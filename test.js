var terminal = require('child_process').spawn('ingenico',{cwd:"./ingenico"});

terminal.stdout.on('data', function (data) 
{
    if(data.toString().trim() == "CONNECTED")
    {
        console.log(data.toString().trim());
        terminal.stdin.write('PAIRING\n');
    }
    
});

terminal.on('exit', function (code) {
    console.log('child process exited with code ' + code);
});

terminal.stdin.write('PING\n');
