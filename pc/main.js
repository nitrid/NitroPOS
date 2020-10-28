const electron = require('electron');
const url = require('url');
const path = require('path');
const fs = require("fs");

const {app,BrowserWindow,Menu} = electron;
app.allowRendererProcessReuse = false
let mainWindow;
let SettingWindow;

app.on('ready',function()
{
    fs.readFile('config.json', function (err, data) 
    {
        if (err) 
        {
          return console.error(err);
        }

        mainWindow = new BrowserWindow(
        {
            webPreferences: 
            {
                nodeIntegration: true,
                nodeIntegrationInWorker: true
            }
        });
        mainWindow.maximize();
        
        let TmpConfig = JSON.parse(data.toString())
        mainWindow.loadURL(TmpConfig.host);
        
        // const mainMenu = Menu.buildFromTemplate(mainMenuTemplate)
        // Menu.setApplicationMenu(mainMenu);
    });
});
function OpenSettings()
{
    SettingWindow = new BrowserWindow(
    {
        width:400,
        height:200,
        title:"Settings"
    });
    SettingWindow.setResizable(false);

    SettingWindow.loadURL(url.format(
    {
        pathname:path.join(__dirname,"Settings.html"),
        protocol:'file',
        slashes:true    
    }))
}
const mainMenuTemplate = 
[
    {
        label : "Settings",
        click () 
        {
            OpenSettings();
        }
    }
]
