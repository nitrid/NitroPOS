var Ingenico = 
(
    function()
    {
        let Terminal;
        let Pairing = false;
        let Listeners = Object();

        if(typeof require == 'undefined')
        {
            return Ingenico;
        }

        function Ingenico()
        {
           
        }        

        Ingenico.prototype.Init = function()
        {
            if(Pairing)
            {
                return;
            }

            Terminal = require('child_process').spawn('ingenico',{cwd:"./ingenico"});
            Terminal.stdin.write('PING\n');
            //console.log("PING")
            Terminal.stdout.on('data', function (data) 
            {
                console.log(data.toString().trim())
                if(data.toString().trim().split('|')[0] == "PING")
                {
                    LocalEvent({tag:"PING",msg:data.toString().trim().split('|')[1]});
                    console.log(data.toString().trim());

                    if(data.toString().trim().split('|')[1] == "CONNECTED")
                    {
                        Terminal.stdin.write('PAIRING\n');
                    }
                }
                else if(data.toString().trim().split('|')[0] == "PAIRING")
                {
                    Pairing = true;
                    LocalEvent({tag:"PAIRING",msg:data.toString().trim().split('|')[1]});                    
                    console.log(data.toString().trim().split('|')[1]);
                }
                else if(data.toString().trim().split('|')[0] == "ITEM_SALE")
                {
                    LocalEvent({tag:"ITEM_SALE",msg:data.toString().trim().split('|')[1]});
                    console.log(data.toString().trim().split('|')[1]);
                }
            });
        }
        Ingenico.prototype.SendData = function(pData)
        {
            console.log(JSON.stringify(pData));
            //Terminal.stdin.write('ITEM_SALE|{"SALES":[{"NAME":"ÜLKER 100 GRM","QUANTITY":2,"AMOUNT":450,"TAX":1}],"PAYMENT":[{"TYPE":0,"AMOUNT":900}]}\n')
            Terminal.stdin.write('ITEM_SALE|' + JSON.stringify(pData) +'\n');
        }
        Ingenico.prototype.TicketClose = function()
        {
            Terminal.stdin.write('TICKET_CLOSE\n');
        }
        //#region "EVENT TRIGGER"        
        function LocalEvent(pData)
        {
            EventTrigger('IngenicoEvent',pData);
        }
        function EventTrigger(evt, params) 
        {
            if (evt in Listeners) 
            {
                callbacks = Listeners[evt];
                for (var x in callbacks)
                {
                    callbacks[x](params);
                }
            } 
            else
            {
                console.log("No listeners found for " + evt);
            }
        }
        Ingenico.prototype.On = function(evt, callback) 
        {
            if (!Listeners.hasOwnProperty(evt))
                Listeners[evt] = Array();
    
                Listeners[evt].push(callback);      
        }
        Ingenico.prototype.Emit = EventTrigger;
        //#endregion EVENT TRIGGER
        return Ingenico;
    }
)();