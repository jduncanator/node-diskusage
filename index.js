var native = require("./build/Release/diskusage.node");

exports.check = function(path, callback) {
  if (callback) {
    return check(path, callback);
  }

  return new Promise(function (resolve, reject) {
      check(path, function (err, result) {
          err ? reject(err) : resolve(result)
      })
  })
};

exports.checkSync = native.getDiskUsage;

function check(path, callback) {
  var result = undefined;
  var error = undefined;

  try {
    result = native.getDiskUsage(path);
  } catch (error_) {
    error = error_;
  }

  callback(error, result);
}
