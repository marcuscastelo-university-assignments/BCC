const possibleColors = ["IndianRed","LightCoral","Salmon","DarkSalmon","LightSalmon","Crimson","Red","FireBrick","DarkRed","Pink","LightPink","HotPink","DeepPink","MediumVioletRed","PaleVioletRed","LightSalmon","Coral","Tomato","OrangeRed","DarkOrange","Orange","Gold","Yellow","LightYellow","LemonChiffon","LightGoldenrodYellow","PapayaWhip","Moccasin","PeachPuff","PaleGoldenrod","Khaki","DarkKhaki","Lavender","Thistle","Plum","Violet","Orchid","Fuchsia","Magenta","MediumOrchid","MediumPurple","RebeccaPurple","BlueViolet","DarkViolet","DarkOrchid","DarkMagenta","Purple","Indigo","SlateBlue","DarkSlateBlue","MediumSlateBlue","GreenYellow","Chartreuse","LawnGreen","Lime","LimeGreen","PaleGreen","LightGreen","MediumSpringGreen","SpringGreen","MediumSeaGreen","SeaGreen","ForestGreen","Green","DarkGreen","YellowGreen","OliveDrab","Olive","DarkOliveGreen","MediumAquamarine","DarkSeaGreen","LightSeaGreen","DarkCyan","Teal","Aqua","Cyan","LightCyan","PaleTurquoise","Aquamarine","Turquoise","MediumTurquoise","DarkTurquoise","CadetBlue","SteelBlue","LightSteelBlue","PowderBlue","LightBlue","SkyBlue","LightSkyBlue","DeepSkyBlue","DodgerBlue","CornflowerBlue","MediumSlateBlue","RoyalBlue","Blue","MediumBlue","DarkBlue","Navy","MidnightBlue","Cornsilk","BlanchedAlmond","Bisque","NavajoWhite","Wheat","BurlyWood","Tan","RosyBrown","SandyBrown","Goldenrod","DarkGoldenrod","Peru","Chocolate","SaddleBrown","Sienna","Brown","Maroon","White","Snow","HoneyDew","MintCream","Azure","AliceBlue","GhostWhite","WhiteSmoke","SeaShell","Beige","OldLace","FloralWhite","Ivory","AntiqueWhite","Linen","LavenderBlush","MistyRose","Gainsboro","LightGray","Silver","DarkGray","Gray","DimGray","LightSlateGray","SlateGray","DarkSlateGray","Black"].map(a=>a.toLowerCase());
function getRandomColor() {
    const color = possibleColors[ Math.floor(Math.random()*(possibleColors.length-1)) ];
    return color;
}


let dynamicSelected = false;
let selectedOutput = undefined;

/**
 * 
 * @param {HTMLDivElement} divElement 
 * @param {string} color 
 */

function setDivColor(divElement, color) {
    divElement.classList = [color];
    divElement.style.backgroundColor = color;
    if (dynamicSelected) selectedOutput.innerHTML = color;
}

/**
 * 
 * @param {HTMLDivElement} divElement 
 */
function startDynamicDiv(divElement) {
    
    const func = () => {
        let color = getRandomColor();
        setDivColor(divElement, color);
    }

    func();
    setInterval(func, 500);
}



window.addEventListener("DOMContentLoaded", function(e) {
    document.getElementById('change_heading').innerText = "Welcome to index.html";
    selectedOutput = document.getElementsByClassName('selected')[0];


    let section = document.getElementsByTagName('section')[0];

    let dynamicDiv = document.createElement('div');
    startDynamicDiv(dynamicDiv);

    dynamicDiv.addEventListener('mouseenter', _ => dynamicSelected = true);
    dynamicDiv.addEventListener('mouseleave', _ => dynamicSelected = false);
    

    section.appendChild(dynamicDiv);

    for (let coloredBox of section.children) {
        coloredBox.addEventListener('mouseenter', function(e){ selectedOutput.innerHTML = this.classList[0]});
        coloredBox.addEventListener('mouseleave', (e) => selectedOutput.innerHTML = 'None!');
    }

});
