# Pynq v2.6.0 Build configuration files
These files reflect the description found in the `README.md` at steps 6, 7, 8, and 9 of the *Build Process*.
- `bluetooth.cfg`: contains the necessary build variables that are needed to add to the *Linux kernel* the necessary modules to enable Bluetooth support. In particular, the `btusb` module is of particular interest for this project.
- `linux-xlnx_%.bbappend`: it is a ready-to-use version of the BitBake Append file which needs to be modified during the *Build Process*.