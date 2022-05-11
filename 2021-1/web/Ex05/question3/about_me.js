window.onload = function() {
    let body = document.getElementsByTagName('body')[0];
    body.style.fontFamily = 'Arial';
    body.style.fontVariant= 'normal';
    body.style.fontWeight = 'bold';
    body.style.fontStyle = 'italic';
    body.style.fontSize = '20px';

    let nicknames = document.getElementById('nickname');
    nicknames.innerHTML = 'marucs';

    let favorites = document.getElementById('favorites');
    favorites.innerHTML = 'metal, anime, coding'

    let hometown = document.getElementById('hometown');
    hometown.innerHTML = 'Santos/SP'

    let img = document.createElement('img');
    img.src = 'https://avatars.githubusercontent.com/u/27441558?v=4'
    img.style.maxWidth='90px'

    let h1 = document.getElementsByTagName('h1')[0];
    h1.insertAdjacentElement('afterend', img);
}