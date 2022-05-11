
function loadInfo(id) {
    return new Promise((res, rej) => {
        let xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState === 4) {
                if (this.status === 200)
                    return res(JSON.parse(this.response))
                else
                    return rej(new Error(`HTTP Error code: ${this.status} \nresponse = ${JSON.stringify(JSON.parse(this.response), null, 4)}`))
            }
        };

        xhttp.open('GET', `https://reqres.in/api/unknown/${id}`, true);
        xhttp.send();
    });
}

async function loadInfoAsync(id) {
    try {
        return await loadInfo(id);
    } catch (e) {
        alert(e);
        return null;
    }
}

async function changeColor(id) {
    const ch = document.getElementById("color-hex");
    const cn = document.getElementById("color-name");
    const cd = document.getElementById("color-display");

    const res = await loadInfoAsync(id);

    if (res) {
        ch.innerText = res.data.color;
        cn.innerText = res.data.name;
        cd.style.backgroundColor = res.data.color;
    };
}


window.addEventListener('DOMContentLoaded', () => {
    changeColor(4);
    const changeBtn = document.getElementById('change-color-btn');
    const colorInput = document.getElementById('color-id');

    changeBtn.addEventListener('click', () => changeColor(parseInt(colorInput.value)));
});