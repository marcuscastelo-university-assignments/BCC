/**
 * @param {string} text 
 * @param {RegExp} _regex
 */
function matchRegex(text, _regex) {
    //Copy regex to keep the original untouched (weird .exec behaviour)
    let regex = RegExp(_regex)

    let results = [];

    while (true) {
        let result = regex.exec(text);
        if (!result) break;
        results.push(result["1"]);
    }

    return results;
}

/**
 * 
 * @param {string} text
 */
function colorize(text) {
    const colorTypeCount = 3;
    const regWord45 = /\b(\w{4,5})\b/;
    const regWord6 = /\b(\w{6})\b/;
    const regWord8M = /\b(\w{8,}\b)/;

    const regs = [regWord45, regWord6, regWord8M];
    const colors = [
        ['purple', 'white'],
        ['blue', 'white'],
        ['pink', 'black']
    ];
    const genColoredSpan = (color, text) => `<span style="background-color: ${color[0]}; color: ${color[1]}">${text}</span>`;

    const regWord = /(\b\w+\b)/gm;

    let toReplace = {}

    let words = matchRegex(text, regWord);
    console.log(words)
    for (let word of words) {
        for (let i = 0; i < colorTypeCount; i++) {
            if (regs[i].test(word)) {
                toReplace[word] = i;
                break;
            }
        }
    }

    for (let word of Object.keys(toReplace)) {
        let i = toReplace[word];
        let coloredWord = genColoredSpan(colors[i], word);
        // let coloredWord = `[${word}]`
        console.log(word)
        const re = new RegExp(`\\b${word}\\b`);
        text = text.replace(re, coloredWord);
    }

    return text;
}

/**
 * @param text {String}
 */
function countWords(text) {
    const regWord = /\b\w+\b/mg;
    return matchRegex(text, regWord).length;
}

function getSentences(html) {
    //Gather all sentences
    const regSentence = /([^.!?;]+[.!?;])/mg;
    let sentences = matchRegex(html, regSentence);
    console.log(sentences);
    return sentences;
}

function doNormalStuff() {
    let p;
    {
        let ps = document.getElementsByTagName('p');
        if (ps.length > 0) p = ps[0];
        else return alert('Error, <p> not found');
    }

    let html = p.innerHTML;

    const sentences = getSentences(html);

    //Count words in each sentence and add them all up
    let wordCount = sentences.map(countWords).reduce((a, b) => a + b);
    let counter = document.createElement('span');
    counter.innerText = `Words: ${wordCount}`;
    let h1s = document.getElementsByTagName('h1');
    if (h1s && h1s.length > 0) h1s[0].insertAdjacentElement('beforebegin', counter);

    
    //Create link
    let a = document.createElement('a');
    a.href = '#';
    a.innerText = 'Home'
    p.insertAdjacentElement('afterend', a);

}

function doBtnStuff() {
    let p;
    {
        let ps = document.getElementsByTagName('p');
        if (ps.length > 0) p = ps[0];
        else return alert('Error, <p> not found');
    }

    let html = p.innerHTML;

    let sentences = getSentences(html);

    //Colorize
    sentences = sentences.map(colorize);

    //Break lines for each colorized sentence
    let newHtml = sentences.reduce((a, b) => `${a} <br><br> ${b}`);
    p.innerHTML = newHtml + '<br>';

}

window.onload = function () {
    doNormalStuff();
    let btn = document.createElement("button");
    btn.innerHTML = "Do Exercise 4 happen!";
    btn.onclick = () => { doBtnStuff(); btn.onclick = undefined; } ;
    document.body.appendChild(document.createElement('br'));
    document.body.appendChild(btn);
}