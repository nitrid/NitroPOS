var Scale = 
(
    function()
    {
        if(typeof require == 'undefined')
        {
            return Scale;
        }
        const SerialPort = require('serialport');

        function Scale()
        {
           
        }

        function _Send(pCallback)
        {
            let port = new SerialPort("COM2",{baudRate:9600,dataBits:8,parity:'none',stopBits:1,xon:true,xoff:true});
            //TERAZİYE İSTEK GÖNDERİLİYOR.
            port.write('$');
            port.on('data',line =>
            {
                console.log(line.toString());  
            });

            return new Promise(function(resolve)
            {
                return port.on("close", resolve)
            });
        }

        Scale.prototype.Send = _Send;
        return Scale;
    }
)();