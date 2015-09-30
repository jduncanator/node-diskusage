node-diskusage
==============

This module implements platform specific bindings to obtain disk usage information on Windows and *nix platforms. Windows support is backed by [GetDiskFreeSpaceEx](http://msdn.microsoft.com/en-us/library/windows/desktop/aa364937/) and *nix is implemented with [statvfs](http://www.freebsd.org/cgi/man.cgi?query=statvfs).

Installation
------------

Install with `npm`:

``` bash
$ npm install diskusage
```

Usage
--------

The module exposes a single function, `check`. It takes a path/mount point as the first argument and a callback as the second. The callback takes two arguments `err` and `info`. `err` will be non-zero if somethine went wrong. `info` contains three members: `available`, `free` and `total` in bytes.

- `available`: Disk space available to the current user (i.e. Linux reserves 5% for root)
- `free`: Disk space physically free
- `total`: Total disk space (free + used)

### Linux Note
`statvfs` under Linux also counts for mount points mounted under the root mount. For example using the mount point `/` as the first parameter would also account for `/dev`, `/run`, etc. in the free and total spaces.

Examples
--------

### Windows
``` js
var disk = require('diskusage');

// get disk usage. Takes path as first parameter
disk.check('c:', function(err, info) {
	console.log(info.available);
	console.log(info.free);
	console.log(info.total);
});
```

### Linux
``` js
var disk = require('diskusage');

// get disk usage. Takes mount point as first parameter
disk.check('/', function(err, info) {
	console.log(info.available);
	console.log(info.free);
	console.log(info.total);
});
```
