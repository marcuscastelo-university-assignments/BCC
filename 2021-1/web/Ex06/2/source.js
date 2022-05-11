
function isJoeHappy(happy, callback) {
    setTimeout(() => {
        const happyness = Math.random()
        if (happyness > happy) {
            callback(happyness);
        } else {
            callback(new Error("Joe is sad!"));
        }
    }, 2000);
}

function promiseJoeIsHappy(happy) {
    return new Promise((res, rej) => {
        isJoeHappy(happy, (cbRes) => {
            if (cbRes instanceof Error) return rej(cbRes);
            else return res(cbRes);
        });
    });
}

async function isJoeAsynchronouslyHappy(happy) {
    return await promiseJoeIsHappy(happy);
}

function hideJoes(idx) {
    const joes = window.joeContainers[idx].getElementsByClassName('joe')
    for (let joe of joes) joe.style.display = "none";
}

function joeIsHappy(idx, hapiness) {
    hideJoes(idx);
    window.joeContainers[idx].getElementsByClassName('joe-happy')[0].style.display = "unset";
    window.joeContainers[idx].getElementsByClassName('hapiness')[0].innerText = 100 * hapiness;
}

function joeIsSad(idx) {
    hideJoes(idx);
    window.joeContainers[idx].getElementsByClassName('joe-sad')[0].style.display = "unset";
}


const evListeners = [
    (idx, threshold) => isJoeHappy(threshold, result => result instanceof Error ? joeIsSad(idx, result) : joeIsHappy(idx, result)),
    (idx, threshold) => promiseJoeIsHappy(threshold).then(r => joeIsHappy(idx, r)).catch(_ => joeIsSad(idx)),
    async (idx, threshold) => {
        try {
            const result = await isJoeAsynchronouslyHappy(threshold);
            joeIsHappy(idx, result);
        }
        catch (e) {
            joeIsSad(idx);
        }
    }
];

window.onload = _ => {
    window.joeBtns = document.getElementsByClassName('joe-btn');
    window.thresholdInps = document.getElementsByClassName('threshold-inp');
    window.joeContainers = document.getElementsByClassName('joe-happiness-container');
    
    console.log(window.joeBtns)
    let i = 0;
    for (let joeBtn of window.joeBtns) {
        hideJoes(i);
        joeBtn.addEventListener('click', (idx => _ => evListeners[idx](idx, window.thresholdInps[idx].value))(i));
        i++;
    }

};