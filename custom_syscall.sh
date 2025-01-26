#!/bin/bash

# Exit immediately if any command fails
set -e

echo "Starting custom syscall setup..."

# Step 1: Update and install required packages
echo "Installing required packages..."
sudo apt-get update || apt-get update
sudo apt-get install     build-essential     libncurses-dev     libssl-dev     libelf-dev     bison     flex     wget     bc     kmod   tree -y  || \
apt-get install     build-essential     libncurses-dev     libssl-dev     libelf-dev     bison     flex     wget     bc     kmod   tree -y 

# Step 2: Download the Linux kernel source
KERNEL_VERSION="6.12.9"
KERNEL_URL="https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-${KERNEL_VERSION}.tar.xz"
KERNEL_DIR="${HOME}/linux-${KERNEL_VERSION}"

echo "Downloading Linux kernel source (version ${KERNEL_VERSION})..."
wget -P "${HOME}" "${KERNEL_URL}"

echo "Extracting Linux kernel source..."
tar -xvf "${HOME}/linux-${KERNEL_VERSION}.tar.xz" -C "${HOME}"

# Step 3: Navigate to the kernel directory
cd "${KERNEL_DIR}"

# Step 4: Create a directory for the new syscall and write the code
SYS_CALL_DIR="${KERNEL_DIR}/test_call"
mkdir -p "${SYS_CALL_DIR}"
echo "Creating custom syscall files..."


