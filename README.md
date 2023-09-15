node-diskusage
==============

<p align="center">
  <a href="https://www.npmjs.com/package/diskusage"><img src="https://img.shields.io/npm/v/diskusage.svg" alt="npm Version" title="npm Version" /></a>
  <a href="https://npm-stat.com/charts.html?package=diskusage"><img src="https://img.shields.io/npm/dw/diskusage.svg" alt="npm Downloads" title="npm Downloads" /></a>
</p>

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

If no callback is supplied `check` will instead return a `Promise<DiskUsage>` that you can await.

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

// Callbacks
disk.check(path, function(err, info) {
  if (err) {
    console.log(err);
  } else {
    console.log(info.available);
    console.log(info.free);
    console.log(info.total);
  }
});

// Promise
async function getFreeSpace(path) {
  try {
    const { free } = await disk.check(path);
    console.log(`Free space: ${free}`);
    return free
  } catch (err) {
    console.error(err)
    return 0
  }
}

// Or without using async/await
disk.check(path)
  .then(info => console.log(`free: ${info.free}`))
  .catch(err => console.error(err))

// Synchronous
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

```ts
type DiskUsage = {
    available: number;
    free: number;
    total: number;
}

export function check(path: string, callback: (error?: Error, result?: DiskUsage) => void): void;
export function check(path: string): Promise<DiskUsage>
export function checkSync(path: string): DiskUsage;
```

Demo
----

To see a demo of this library see the `demo/` folder.

You can run it with node: (node 8+ required)

```bash
node ./demo/
```
