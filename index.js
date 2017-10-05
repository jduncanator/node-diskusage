var native = require('./build/Release/diskusage.node');

exports.check = function(path, callback) {
    var result = undefined;
    var error = undefined;
    try {
        result = native.getDiskUsage(path);
    }
    catch (error_) {
        error = error_
    }
    callback(error, result);
};

exports.checkSync = native.getDiskUsage;
