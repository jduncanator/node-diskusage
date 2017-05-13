node-diskusage
==============

This module implements platform specific bindings to obtain disk usage information on Windows and POSIX platforms. Windows support is backed by [GetDiskFreeSpaceEx](http://msdn.microsoft.com/en-us/library/windows/desktop/aa364937/) and POSIX is implemented with [statvfs](http://www.freebsd.org/cgi/man.cgi?query=statvfs).

Installation
------------

Install with `npm`:

``` bash
$ npm install diskusage
```

Usage
--------

The module exposes two functions. `check` takes a path/mount point as the first argument and a callback as the second. The callback takes two arguments `err` and `info`. `err` will be an `Error` if something went wrong. `info` contains three members: `available`, `free` and `total` in bytes.

- `available`: Disk space available to the current user (i.e. Linux reserves 5% for root)
- `free`: Disk space physically free
- `total`: Total disk space (free + used)

`checkSync` only takes the path argument. It returns the same `info` on success, throws an `Error` on failure.

Examples
--------

``` js
const disk = require('diskusage');
const os = require('os');

let path = os.platform() === 'win32' ? 'c:' : '/';

disk.check(path, function(err, info) {
	if (err) {
		console.log(err);
	} else {
		console.log(info.available);
		console.log(info.free);
		console.log(info.total);
	}
});

try {
	let info = disk.checkSync(path);
	console.log(info.available);
	console.log(info.free);
	console.log(info.total);
}
catch (err) {
	console.log(err);
}
```

TypeScript
----------

The module has an embedded .d.ts file. You can use `import * as diskusage from 'diskusage'`.

```
type DiskUsage = {
    available: number;
    free: number;
    total: number;
}

export function check(path: string, callback: (error: Error, result: DiskUsage) => void): void;
export function checkSync(path: string): DiskUsage;
```
