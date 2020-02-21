var scope = {};

function call(msg) {
  var exp = msg.toString();
  console.log(exp);
  var data = { expression: msg }
  try {
    var func = new Function(`return (${exp});`); 
    data.result = JSON.stringify(func.call(scope), null, 2);
    console.log("scope: " + JSON.stringify(scope, null, 2) + "result: " + data.result);
  } catch (err) {
    console.log(e.toString());
    data.error = err.toString();
  }
  return data;
}