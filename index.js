var ffi = require('ffi')
  , ref = require('ref');

if(process.platform == 'win32') {
    var ulongPtr = ref.refType(ref.types.uint64);
    var DiskApi = ffi.Library('kernel32', {
        'GetDiskFreeSpaceExA': [ 'int', [ 'string', ulongPtr, ulongPtr, ulongPtr ] ]
    })

    exports.check = function(drive, callback) {
        var freeBytesPtr = ref.alloc(ref.types.uint64)
          , totalBytesPtr = ref.alloc(ref.types.uint64);
        var returnCode = DiskApi.GetDiskFreeSpaceExA(drive, freeBytesPtr, totalBytesPtr, ref.NULL_POINTER);
        if(!returnCode) {
            callback(returnCode, undefined);
        } else {
            callback(undefined, { 
                free: freeBytesPtr.deref(),
                total: totalBytesPtr.deref()
            });
        }
    }
} else if(process.platform == 'linux' || 
          process.platform == 'freebsd' || 
          process.platform == 'darwin' ||
          process.platform == 'sunos' ) {
    
    var Struct = require('ref-struct')
      , ArrayType = require('ref-array');

    var fsblkcnt_t = (process.platform == 'darwin') ? ref.types.uint : ref.types.ulong
      , fsfilcnt_t = (process.platform == 'darwin') ? ref.types.uint : ref.types.ulong
      , ulong = ref.types.ulong
      , char = ref.types.char;

    var statvfs_t = Struct({
        'f_bsize': ulong,                       /* fundamental file system block size */
        'f_frsize': ulong,                      /* fragment size */
        'f_blocks': fsblkcnt_t,                 /* total blocks of f_frsize on fs */
        'f_bfree': fsblkcnt_t,                  /* total free blocks of f_frsize */
        'f_bavail': fsblkcnt_t,                 /* free blocks avail to non-superuser */
        'f_files': fsfilcnt_t,                  /* total file nodes (inodes) */
        'f_ffree': fsfilcnt_t,                  /* total free file nodes */
        'f_favail': fsfilcnt_t,                 /* free nodes avail to non-superuser */
        'f_fsid': ulong,                        /* file system id (dev for now) */
        'f_basetype': ArrayType(char, 16),      /* target fs type name, null-terminated */
        'f_flag': ulong,                        /* bit-mask of flags */
        'f_namemax': ulong,                     /* maximum file name length */
        'f_fstr': ArrayType(char, 32),          /* filesystem-specific string */
        'f_filler': ArrayType(ulong, 16)        /* reserved for future expansion */
    });

    // Do we depend on libc being loaded in the Node procces?
    var DiskApi = ffi.Library(null, {
        'statvfs': [ 'int', [ 'string', ref.refType(statvfs_t) ] ]
    })

    exports.check = function(drive, callback) {
        var statvfs = new statvfs_t();
        var returnCode = DiskApi.statvfs(drive, statvfs.ref());

        if(returnCode) {
            callback(returnCode, undefined);
        } else {
            callback(undefined, { 
                free: statvfs.f_bfree * statvfs.f_frsize,
                total: statvfs.f_blocks * statvfs.f_frsize
            });
        }
    }
}
