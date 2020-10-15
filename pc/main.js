const electron = require('electron');
const url = require('url');
const path = require('path');
const storage = require('electron-localStorage');

const {app,BrowserWindow,Menu} = electron;
app.allowRendererProcessReuse = false
let mainWindow;

app.on('ready',function()
{
    mainWindow = new BrowserWindow(
    {
        webPreferences: 
        {
            nodeIntegration: true,
            nodeIntegrationInWorker: true
        }
    });
    storage.setItem("test","11");
    console.log(storage.getItem("test"));
    mainWindow.loadURL('http://localhost');

    // const mainMenu = Menu.buildFromTemplate(mainMenuTemplate)
    // Menu.setApplicationMenu(mainMenu);
});

const mainMenuTemplate = 
[
    {
        label : "Settings"
    }
]
