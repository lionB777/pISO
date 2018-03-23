use error::{ErrorKind, Result};
use lvm;
use usb;
use utils;
use std::fs;
use std::path::{Path, PathBuf};
use std::sync::{Arc, Mutex};
use std::time::Duration;

const VDRIVE_MOUNT_ROOT: &str = "/mnt";

pub enum MountState {
    Unmounted,
    Internal(Vec<PathBuf>),
    External(usb::StorageID),
}

pub struct VirtualDrive {
    pub state: MountState,
    pub usb: Arc<Mutex<usb::UsbGadget>>,
    pub volume: lvm::LogicalVolume,
}

impl VirtualDrive {
    pub fn new(
        volume: lvm::LogicalVolume,
        usb: Arc<Mutex<usb::UsbGadget>>,
    ) -> Result<VirtualDrive> {
        Ok(VirtualDrive {
            state: MountState::Unmounted,
            usb: usb,
            volume: volume,
        })
    }

    pub fn name(&self) -> &str {
        &self.volume.name
    }

    pub fn mount_external(&mut self) -> Result<()> {
        match self.state {
            MountState::External(_) => Ok(()),
            MountState::Unmounted => {
                let id = self.usb
                    .lock()
                    .map_err(|_| "Failed to lock usb mutex")?
                    .export_file(&self.volume.path, false)?;
                self.state = MountState::External(id);
                Ok(())
            }
            MountState::Internal(_) => {
                Err("Attempt to mount_external while mounted internal".into())
            }
        }
    }

    pub fn unmount_external(&mut self) -> Result<()> {
        match self.state {
            MountState::Unmounted => {}
            MountState::Internal(_) => {
                return Err("Attempt to unmount_external while mounted internal".into());
            }
            MountState::External(ref id) => {
                self.usb
                    .lock()
                    .map_err(|_| "Failed to lock usb mutex")?
                    .unexport_file(id)?;
            }
        }
        self.state = MountState::Unmounted;
        Ok(())
    }

    fn mount_partition<P1, P2>(&self, device: P1, target: P2) -> Result<()>
    where
        P1: AsRef<Path>,
        P2: AsRef<Path>,
    {
        let mounters = &["mount", "mount.exfat"];
        for mounter in mounters {
            let fsmount = utils::run_check_output(mounter, &[device.as_ref(), target.as_ref()]);
            if fsmount.is_ok() {
                return Ok(());
            }
        }
        Err(format!(
            "Failed to mount: {} to {}",
            device.as_ref().display(),
            target.as_ref().display()
        ).into())
    }

    pub fn mount_internal(&mut self) -> Result<()> {
        match self.state {
            MountState::Unmounted => {
                let volume_path = &self.volume.path.to_string_lossy();
                let loopback_path =
                    PathBuf::from(utils::run_check_output("losetup", &["-f"])?.trim_right());
                let loopback_name: String = loopback_path
                    .file_name()
                    .ok_or(ErrorKind::Msg("loopback path has no file name".into()))?
                    .to_string_lossy()
                    .into();

                utils::run_check_output("losetup", &["-fPL", volume_path])?;
                utils::wait_for_path(&loopback_path, Duration::from_millis(1000))?;
                utils::run_check_output("partprobe", &[loopback_path])?;

                let mut mounted_partitions = vec![];
                for entry in fs::read_dir("/dev")? {
                    let entry = entry?;
                    if entry
                        .file_name()
                        .to_string_lossy()
                        .starts_with(&loopback_name)
                    {
                        let mount_point = Path::new(VDRIVE_MOUNT_ROOT).join(entry.file_name());
                        fs::create_dir_all(&mount_point)?;
                        if self.mount_partition(&entry.path(), &mount_point).is_ok() {
                            mounted_partitions.push(mount_point.to_path_buf());
                        }
                    }
                }
                self.state = MountState::Internal(mounted_partitions);
                Ok(())
            }
            MountState::Internal(_) => Ok(()),
            MountState::External(_) => {
                Err("Attempt to mount_internal while mounted external".into())
            }
        }
    }

    pub fn unmount_internal(&mut self) -> Result<()> {
        match self.state {
            MountState::Unmounted => {}
            MountState::Internal(ref partitions) => for part in partitions {
                utils::run_check_output("umount", &[part])?;
            },
            MountState::External(_) => {
                return Err("Attempt to unmount_internal while mounted external".into());
            }
        };
        self.state = MountState::Unmounted;
        Ok(())
    }
}