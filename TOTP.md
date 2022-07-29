# TOTP on STM32

## Overview
This project aims to implement a TOTP (Time-based One Time Password) program on a STM32 MCU that is compatible with Google Authenticator and Authy's [Key URI Format](https://github.com/google/google-authenticator/wiki/Key-Uri-Format). 

Example: 
> otpauth://totp/Example:alice@google.com?secret=JBSWY3DPEHPK3PXP&issuer=Example

As TOTP is a variation of HOTP, which in turn relies on HMAC and a cryptographic hashing function such as SHA-1, this project uses WolfSSL as a lightweight cryptographic library solution on embedded platforms. 

## Note
Google Authenticator, and a majority of TOTP implementations, uses a 64-bit integer to store epoch time (fed into HMAC as HTOP's counter). While this practice does not seem to have been regulated in the original RFC document, it is more desirable to follow the current de-facto standards. 

Another noteworthy behavior is that the keys in URIs are base32-encoded to prevent direct exposure. 

## References
- [TOTP: Time-Based One-Time Password Algorithm](https://datatracker.ietf.org/doc/html/rfc6238)
- [Portable Symmetric Key Container (PSKC)](https://datatracker.ietf.org/doc/html/rfc6030)
- [MinTOTP: Minimal TOTP generator in 20 lines of Python](https://github.com/susam/mintotp)
- [OTPAuth: One Time Password (HOTP/TOTP) library for Node.js, Deno and browsers. ](https://github.com/hectorm/otpauth)