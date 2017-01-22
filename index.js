var native = require('./build/Release/diskusage.node');

exports.check = function(path, callback) {
    try {
        callback(undefined, native.getDiskUsage(path));
    }
    catch (error) {
        callback(error, undefined);
    }
};

exports.checkSync = native.getDiskUsage;
