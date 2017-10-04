const native = require('./build/Release/diskusage.node');

exports.check = function(path, callback) {
    let result = null;
    let error = null;
    try {
        result = native.getDiskUsage(path);
    }
    catch (error_) {
        error = error_
    }
    callback(error, result);
};

exports.checkSync = native.getDiskUsage;
