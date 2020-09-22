let SqlLib = require("../sql/sqllib");
let Process = require("./process");

_Start();
function datasync() 
{

}
datasync.prototype.Start = _Start;
datasync.prototype.DataTransfer = _DataTransfer;
datasync.prototype.Process = Process;

function _Start() 
{
    for (let i = 0;i < Process.length;i++)
    {
        if(typeof Process[i].auto != 'undefined')
        {
            setTimeout(StartTransfer,Process[i].auto,{...Process[i]});
        }
    }
}
async function StartTransfer(pParam)
{
    await _DataTransfer({...pParam});
    setTimeout(StartTransfer,pParam.auto,{...pParam})
}
function _DataTransfer(pParam)
{
    return  new Promise(async resolve =>
    {
        console.log(pParam.name + " Kayıtları Aktarılıyor.")
        let SData = await GetData(pParam.select,pParam.source);

        for (let i = 0;i < SData.length;i++)
        {
            if(typeof pParam.control != 'undefined')
            {
                //EĞER UPDATE AKTİF İSE KAYITLAR KONTROL EDİLİP UPDATE EDİLİYOR
                let CtrlData = await GetData(BuildQueryParam(pParam.control,SData[i]),pParam.target);
            
                if(typeof CtrlData != 'undefined')
                {
                    if(CtrlData.length > 0)
                    {
                        //UPDATE
                        if(typeof pParam.update != 'undefined')
                        {
                            await Execute(BuildQueryParam(pParam.update,SData[i]),pParam.target);
                        }
                    }
                    else
                    {
                        //INSERT
                        await Execute(BuildQueryParam(pParam.insert,SData[i]),pParam.target);
                    }
                } 
            }
            else
            {
                //EĞER UPDATE AKTİF DEĞİLSE KAYITLAR SADECE İNSERT EDİLİYOR.KAYIT ÇAKIŞMASINDAN BEN MESUL DEĞİLİM.
                await Execute(BuildQueryParam(pParam.insert,SData[i]),pParam.target);
            }
        }
        console.log(pParam.name + " Aktarımı Bitti.")
        resolve();
    });
}
function GetData(pQuery,pConnet)
{
    return new Promise(resolve =>
    {
        let TmpSql = new SqlLib(pConnet.server,pConnet.database,pConnet.uid,pConnet.pwd,0);

        TmpSql.QueryPromise(pQuery,function(Data)
        {
            if(typeof JSON.parse(Data).err != 'undefined')
            {
                console.log(JSON.parse(Data).err)
            }
            resolve(JSON.parse(Data).recordset);
        });
    });
}
function Execute(pQuery,pConnet)
{
    return new Promise(resolve =>
    {
        let TmpSql = new SqlLib(pConnet.server,pConnet.database,pConnet.uid,pConnet.pwd,0);

        TmpSql.QueryPromise(pQuery,function(Data)
        {
            if(typeof JSON.parse(Data).err != 'undefined')
            {
                console.log(JSON.parse(Data).err)
            }
            resolve();
        });
    });
}
function BuildQueryParam(pQuery,pData)
{
    let TmpValue = [];
    for(let i = 0;i < pQuery.param.length;i++)
    {
        let Column = ""
        if(pQuery.param[i].split(':').length > 1)
            Column = pQuery.param[i].split(":")[0]
        else
            Column = pQuery.param[i];
        
        TmpValue.push(pData[Column]);
    }
    
    if(TmpValue.length > 0)
    {
        pQuery.value = TmpValue;
    }

    return pQuery;
}
module.exports = datasync;