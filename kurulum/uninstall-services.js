var Service = require('node-windows').Service;
const path = require('path');

var svc = new Service
({
    name:'NitroGen POS',
    description: 'NitroGen POS Server.',
    script: path.join(process.cwd(), '..\\server.js'),
    env: 
    [
        {
            name: 'APP_DIR_PATH',
            value: process.cwd()
        }
    ]
});

svc.on('uninstall',function()
{
    svc.stop();
});
svc.uninstall();