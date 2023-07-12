# RELEASE NOTES : #

## v1.5.0 -- January 2023 ##

* feat(fqdn): giving some time for FQDN resolution
* Docker image improvements
* Fixed docker exit by catching SIGTERM
* release mode does not use libasan anymore --> allocation of 20T virtual memory is no longer done
* Ubuntu22 and cgroup2 support

## v1.4.0 -- July 2022 ##

* Remove unused packages
* HTTP/2 support for SBI interface
* NRF Registration and heartbeat exchange
* Official images produced by CI are pushed to `oaisoftwarealliance` Docker-Hub Team account
* Reduce image size

## v1.3.0 -- January 2022 ##

* HTTP2 Support
* Docker optimization

## v1.2.1 -- October 2021 ##

* Fix build issue

## v1.2.0 -- September 2021 ##

* Initial public release
* NRF registration
  - with FQDN DNS resolution
* Full support for Ubuntu18 and RHEL8

## v1.0.0 -- June 2021 ##

* Initial private release
