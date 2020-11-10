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

        function _Send(pPort)
        {
            return new Promise(resolve =>
            {
                let port = new SerialPort(pPort,{baudRate:9600,dataBits:8,parity:'none',stopBits:1,xon:true,xoff:true});
                //TERAZİYE İSTEK GÖNDERİLİYOR.
                port.write('$');
                port.on('data',line =>
                {
                    resolve(line.toString());
                    port.close();
                });

                return port.on("close", resolve)
            });
        }

        Scale.prototype.Send = _Send;
        return Scale;
    }
)();