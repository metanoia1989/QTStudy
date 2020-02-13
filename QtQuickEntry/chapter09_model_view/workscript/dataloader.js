WorkerScript.onMessage = function (msg) {
  if (msg.action === 'appendCurrentTime') {
    var data = { "time": new Date().toTimeString() };
    msg.model.append(data);
    msg.model.sync(); // 更新改动到列表
  }
}