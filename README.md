# System Logger

## Overview
The **System Logger** is a Linux service developed for monitoring system resources on Linux systems. This service is packaged into a `.deb` package for easy installation, deployment, and removal.

## Features
- **Shared Library**: Implements a shared library for functions which get information of Linux system.
- **Systemd Service**: Integrates seamlessly with systemd for managing the service.
- **Logging**: Captures system metrics and logs them efficiently.
- **Logrotate**: Utilizes Logrotate for effective log management.

## Installation
To install the service just download ".deb" file and install by dpkg

```bash
sudo dpkg -i system-logger.deb
