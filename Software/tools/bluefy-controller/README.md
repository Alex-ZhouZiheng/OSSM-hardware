# OSSM Bluefy Controller

This directory contains a standalone Web Bluetooth controller for OSSM.

## iOS / Bluefy usage

Deploy `index.html` to an HTTPS static host, then open that HTTPS URL in
Bluefy on iOS. Web Bluetooth requires a secure browser context, so a normal
local file URL or plain HTTP URL is not a reliable long-term entry point.

Recommended hosts:

- GitHub Pages
- Cloudflare Pages

The page talks directly to OSSM over BLE. Refreshing, closing, hiding, or
disconnecting the page attempts to send `set:speed:0` and `go:menu` before
releasing the Bluetooth connection.
