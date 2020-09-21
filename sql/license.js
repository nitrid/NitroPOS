var MacId = require('node-machine-id');
let fs = require('fs');

var LicIo = require('socket.io-client');
var LicSoc = LicIo.connect('http://licence.teknoticari.com:8090',{'timeout':2000, 'connect timeout': 2000});
let AppId = "03";

// function LicenseCheck(callback)
// {
//     if(typeof callback != 'undefined')
//     {
//         LicSoc.on('connect', function () 
//         {   
//             console.log('MacId : ' + MacId.machineIdSync());
            
//             LicSoc.emit('licensecheck',{MacId:MacId.machineIdSync()},function(data)
//             {
//                 if(data.result.length > 0)
//                 {
//                     callback(data);
//                 }
//                 else
//                 {
//                     callback(data);
//                 }
//             });            
//         });
//         LicSoc.on('connect_error', function (socket) 
//         {
//             callback("");            
//         });
//     }
// }
function LicenseCheck(callback)
{
    if(typeof callback != 'undefined')
    {
        if(LicSoc.connected)
        {
            LicSoc.emit('licensecheck',{MacId: AppId + MacId.machineIdSync()},function(data)
            {
                WriteLic(data);
                callback(data);
            });     
        }
        else
        {
            LicSoc.on('connect', function () 
            {   
                console.log('MacId : ' + AppId + MacId.machineIdSync());
                LicSoc.emit('licensecheck',{MacId: AppId + MacId.machineIdSync()},function(data)
                {
                    WriteLic(data);
                    callback(data);
                });            
            });
            LicSoc.on('connect_error', function (socket) 
            {
                ReadLic(function(data)
                {
                    LicSoc.close();
                    callback(data);
                })
            });
        }
        
    }
}
function WriteLic(pData)
{
    let FilePath = "";
    if(typeof process.env.APP_DIR_PATH != 'undefined')
    {
        FilePath = process.env.APP_DIR_PATH + "/.";
    }

    fs.writeFile(FilePath + "./lic.json",JSON.stringify(pData),function(err)
    {});
}
function ReadLic(pCallback)
{
    let FilePath = "";
    if(typeof process.env.APP_DIR_PATH != 'undefined')
    {
        FilePath = process.env.APP_DIR_PATH + "/.";
    }

    fs.readFile(FilePath + "./lic.json",{encoding: 'utf-8'},function(err,data)
    {
        if (!err) 
        {
            pCallback(JSON.parse(data));
        }
        else
        {
            pCallback("");
        }
    })
}
module.exports.LicenseCheck = LicenseCheck;
