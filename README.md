This repository contains a few c++ utilities, mainly for use in rehax-native and fluxe.

## Components

### Pointers

This is an auto reference counted smart pointer. You use it similar to `std::shared_ptr`, and it exposes methods to increase and decrease the reference count manually.
It is useful if you want to use smart pointers, but you have to pass pointers around to things that aren't aware of smart pointers.

### Timer

An abstraction of timers in various platforms.

### Links

Expose a way to open a URL in the default web browser.
