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

                    if(data.toString().split("~",2)[0].split(":",2)[0] == "PING|SUCCESS")
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
                else if(data.toString().trim().split('|')[0] == "PAYMENT")
                {
                    LocalEvent({tag:"PAYMENT",msg:data.toString().trim().split('|')[1]});
                    console.log(data.toString().trim().split('|')[1]);
                }
                else if(data.toString().trim().split('|')[0] == "PAYMENT_CANCEL")
                {
                    LocalEvent({tag:"PAYMENT_CANCEL",msg:data.toString().trim().split('|')[1]});
                }
                else if(data.toString().trim().split('|')[0] == "TIMEOUT_TICKET_CONTROL")
                {
                    LocalEvent({tag:"TIMEOUT_TICKET_CONTROL",msg:data.toString().trim().split('|')[1]});
                }
                else if(data.toString().trim().split('|')[0] == "HANDLE_CLOSE")
                {
                    LocalEvent({tag:"HANDLE_CLOSE",msg:data.toString().trim().split('|')[1]});
                }
                else if(data.toString().trim().split('|')[0] == "TICKET_CANCEL")
                {
                    LocalEvent({tag:"TICKET_CANCEL",msg:data.toString().trim().split('|')[1]});
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
                }
                else if(data.toString().trim().split('|')[0] == "EKUCONTROL")
                {
                    LocalEvent({tag:"EKUCONTROL",msg:data.toString().trim().split('|')[1]});
                }
                else if(data.toString().trim().split('|')[0] == "TAX_INFO")
                {
                    LocalEvent({tag:"TAX_INFO",msg:data.toString().trim().split('|')[1]});
                }
            });
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
        Ingenico.prototype.EkuControl = function(pCallBack)
        {
            Terminal.stdin.write('EKUCONTROL' + '\n');

            let m = function(data)
            {
                if(data.toString().trim().split('|')[0] == "EKUCONTROL")
                {
                    pCallBack({tag:"EKUCONTROL",msg:data.toString().trim().split('|')[1]});
                    Terminal.stdout.removeListener('data',m);
                }
            }

            Terminal.stdout.on('data', m);
        }
        Ingenico.prototype.Pairing = function()
        {
            Terminal.stdin.write('PAIRING\n');
        }
        //
        Ingenico.prototype.ItemSale = function(pData,pCallBack)
        {
            console.log(JSON.stringify(pData))

            Terminal.stdin.write('ITEM_SALE|' + JSON.stringify(pData) +'\n');

            let m = function(data)
            {
                if(data.toString().trim().split('|')[0] == "ITEM_SALE")
                {
                    pCallBack({tag:"ITEM_SALE",msg:data.toString().trim().split('|')[1]});
                    Terminal.stdout.removeListener('data',m);
                }
            }

            Terminal.stdout.on('data', m);
        }
        Ingenico.prototype.Payment = function(pData,pCallBack)
        {
            console.log(pData);
            
            Terminal.stdin.write('PAYMENT|' + JSON.stringify(pData) +'\n');

            let m = function(data)
            {
                if(data.toString().trim().split('|')[0] == "PAYMENT")
                {
                    pCallBack({tag:"PAYMENT",msg:data.toString().trim().split('|')[1]});
                    Terminal.stdout.removeListener('data',m);
                }
            }

            Terminal.stdout.on('data', m);
        }
        Ingenico.prototype.Invoice = function(pData,pCallBack)
        {
            console.log(JSON.stringify(pData))
            Terminal.stdin.write('INVOICE|' + JSON.stringify(pData) + '\n');

            let m = function(data)
            {
                if(data.toString().trim().split('|')[0] == "INVOICE")
                {
                    pCallBack({tag:"INVOICE",msg:data.toString().trim().split('|')[1]});
                    Terminal.stdout.removeListener('data',m);
                }
            }

            Terminal.stdout.on('data', m);
        }
        Ingenico.prototype.PaymentCancel = function(pData,pCallBack)
        {
            Terminal.stdin.write('PAYMENT_CANCEL|' + JSON.stringify(pData) +'\n');

            let m = function(data)
            {
                if(data.toString().trim().split('|')[0] == "PAYMENT_CANCEL")
                {
                    pCallBack({tag:"PAYMENT_CANCEL",msg:data.toString().trim().split('|')[1]});
                    Terminal.stdout.removeListener('data',m);
                }
            }

            Terminal.stdout.on('data', m);
        }
        Ingenico.prototype.TimeOutTicketControl = function(pCallBack)
        {
            Terminal.stdin.write('TIMEOUT_TICKET_CONTROL' + '\n');

            let m = function(data)
            {
                if(data.toString().trim().split('|')[0] == "TIMEOUT_TICKET_CONTROL")
                {
                    pCallBack({tag:"TIMEOUT_TICKET_CONTROL",msg:data.toString().trim().split('|')[1]});
                    Terminal.stdout.removeListener('data',m);
                }
            }

            Terminal.stdout.on('data', m);
        }
        Ingenico.prototype.HandleClose = function(pCallBack)
        {
            Terminal.stdin.write('HANDLE_CLOSE' + '\n');

            let m = function(data)
            {
                if(data.toString().trim().split('|')[0] == "HANDLE_CLOSE")
                {
                    pCallBack({tag:"HANDLE_CLOSE",msg:data.toString().trim().split('|')[1]});
                    Terminal.stdout.removeListener('data',m);
                }
            }

            Terminal.stdout.on('data', m);
        }
        Ingenico.prototype.TicketCancel = function(pCallBack)
        {
            Terminal.stdin.write('TICKET_CANCEL' + '\n');

            let m = function(data)
            {
                if(data.toString().trim().split('|')[0] == "TICKET_CANCEL")
                {
                    pCallBack({tag:"TICKET_CANCEL",msg:data.toString().trim().split('|')[1]});
                    Terminal.stdout.removeListener('data',m);
                }
            }

            Terminal.stdout.on('data', m);
        }
        Ingenico.prototype.TaxInfo = function(pData,pCallBack)
        {
            Terminal.stdin.write('TAX_INFO|' + JSON.stringify(pData) +'\n');

            let m = function(data)
            {
                if(data.toString().trim().split('|')[0] == "TAX_INFO")
                {
                    pCallBack({tag:"TAX_INFO",msg:data.toString().trim().split('|')[1]});
                    Terminal.stdout.removeListener('data',m);
                }
            }

            Terminal.stdout.on('data', m);
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