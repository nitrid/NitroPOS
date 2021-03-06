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
                else if(data.toString().trim().split('|')[0] == "ZREPORT")
                {
                    LocalEvent({tag:"ZREPORT",msg:data.toString().trim().split('|')[1]});
                    console.log(data.toString().trim().split('|')[1]);
                }
                else if(data.toString().trim().split('|')[0] == "XREPORT")
                {
                    LocalEvent({tag:"XREPORT",msg:data.toString().trim().split('|')[1]});
                    console.log(data.toString().trim().split('|')[1]);
                }
                else if(data.toString().trim().split('|')[0] == "CASEIN")
                {
                    LocalEvent({tag:"CASEIN",msg:data.toString().trim().split('|')[1]});
                    console.log(data.toString().trim().split('|')[1]);
                }
                else if(data.toString().trim().split('|')[0] == "CASEOUT")
                {
                    LocalEvent({tag:"CASEOUT",msg:data.toString().trim().split('|')[1]});
                    console.log(data.toString().trim().split('|')[1]);
                }
                else if(data.toString().trim().split('|')[0] == "ENDCOPY")
                {
                    LocalEvent({tag:"ENDCOPY",msg:data.toString().trim().split('|')[1]});
                    console.log(data.toString().trim().split('|')[1]);
                }
                else if(data.toString().trim().split('|')[0] == "INVOICE")
                {
                    LocalEvent({tag:"INVOICE",msg:data.toString().trim().split('|')[1]});
                    console.log(data.toString().trim().split('|')[1]);
                }
                else if(data.toString().trim().split('|')[0] == "OPENSAFE")
                {
                    LocalEvent({tag:"OPENSAFE",msg:data.toString().trim().split('|')[1]});
                    console.log(data.toString().trim().split('|')[1]);
                }
            });
        }
        Ingenico.prototype.SendData = function(pData)
        {
            console.log(JSON.stringify(pData));
            //Terminal.stdin.write('ITEM_SALE|{"SALES":[{"NAME":"ÜLKER 100 GRM","QUANTITY":2,"AMOUNT":450,"TAX":1,"TYPE":0}],"PAYMENT":[{"TYPE":0,"AMOUNT":900}]}\n')
            Terminal.stdin.write('ITEM_SALE|' + JSON.stringify(pData) +'\n');
        }
        Ingenico.prototype.TicketClose = function()
        {
            Terminal.stdin.write('TICKET_CLOSE\n');
        }
        Ingenico.prototype.ZReport = function(pData)
        {
            Terminal.stdin.write('Z_REPORT|' + pData + '\n');
        }
        Ingenico.prototype.XReport = function(pData)
        {
            Terminal.stdin.write('X_REPORT|' + pData + '\n');
        }
        Ingenico.prototype.CaseIn = function(pData)
        {
            Terminal.stdin.write('CASEIN|' + pData +'\n');
        }
        Ingenico.prototype.CaseOut = function(pData)
        {
            Terminal.stdin.write('CASEOUT|' + pData +'\n');
        }
        Ingenico.prototype.EndCopy = function(pData)
        {
            Terminal.stdin.write('ENDCOPY|' + pData + '\n');
        }
        Ingenico.prototype.OpenSafe = function()
        {
            Terminal.stdin.write('OPENSAFE' + '\n');
        }
        Ingenico.prototype.Invoice = function(pData)
        {
            console.log(JSON.stringify(pData))
            Terminal.stdin.write('INVOICE|' + JSON.stringify(pData) + '\n');
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