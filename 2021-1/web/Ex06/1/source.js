
function loadInfo(id) {
    return new Promise((res, rej) => {
        let xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState === 4 && this.status === 200) {
                res(JSON.parse(this.response))
            }
        };

        xhttp.open('GET', `https://reqres.in/api/unknown/${id}`, true);
        xhttp.send();
    });
}

function changeColor(id) {
    const ch = document.getElementById("color-hex");
    const cn = document.getElementById("color-name");
    const cd = document.getElementById("color-display");

    loadInfo(id).then(res => {
        ch.innerText = res.data.color;
        cn.innerText = res.data.name;
        cd.style.backgroundColor = res.data.color;
    });
}


window.addEventListener('DOMContentLoaded', () => {
    changeColor(4);
    const changeBtn = document.getElementById('change-color-btn');
    const colorInput = document.getElementById('color-id');

    changeBtn.addEventListener('click', () => changeColor(parseInt(colorInput.value)));
});