const { check, checkSync } = require("../");
const os = require("os");

const targetPath = os.platform() === "win32" ? "c:" : "/";

function printResults(type, { available, free, total }) {
  console.log(`${type}
    Available: ${available}
    Free: ${free}
    Tocal: ${total}
  `);
}

async function getFreeSpacePromise(path) {
  try {
    const info = await check(path);
    printResults("PROMISE", info);
  } catch (err) {
    console.error(err);
  }
}

function getFreeSpaceCallback(path) {
  check(path, (err, info) => {
    if (err) {
      console.error(err);
    } else {
      printResults("CALLBACK", info);
    }
  });
}

function getFreeSpaceSync(path) {
  const info = checkSync(path);
  printResults("SYNC", info);
}

async function start() {
  await getFreeSpacePromise(targetPath);
  getFreeSpaceCallback(targetPath);
  getFreeSpaceSync(targetPath);
}

start()