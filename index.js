var fs = require('fs');

// Detect presence of fs.statfs
if(typeof fs.statfs === 'function') {
  exports.check = function(path, callback) {
    if (callback) {
      return check(path, callback);
    }

    return new Promise(function (resolve, reject) {
      check(path, function (err, result) {
        err ? reject(err) : resolve(result);
      });
    });
  }

  function check(path, callback) {
    fs.statfs(path, function (err, result_) {
      var result = undefined;

      if (!err) {
        result = {
          available: result_.bavail * result_.bsize,
          free: result_.bfree * result_.bsize,
          total: result_.blocks * result_.bsize
        };
      }

      callback(err, result);
    });
  }

  exports.checkSync = function(path) {
    var result = fs.statfsSync(path);

    return {
      available: result.bavail * result.bsize,
      free: result.bfree * result.bsize,
      total: result.blocks * result.bsize
    }
  }
} else {
  var diskusage = require('./fallback.js');

  exports.check = diskusage.check;
  exports.checkSync = diskusage.checkSync;
}