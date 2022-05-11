function makeMadTalk(e) {
    let [noun, adjective, name] = document.getElementsByTagName('input');
    const phrase = `${name.value} hates ${adjective.value} ${noun.value}`;

    document.getElementById('story').innerText = phrase;
}


window.onload = function() {
    let btn = document.getElementsByTagName('button')[0];
    btn.onclick = makeMadTalk;
}