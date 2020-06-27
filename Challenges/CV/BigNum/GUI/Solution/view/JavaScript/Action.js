

function GetRandomNumber(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function GetRandomNumbers(){
    var str_nums = '';
    for (var i = 0; i < 1000; i++)
        str_nums += GetRandomNumber(0, 9);
    return str_nums; // Use this if you want random numbers
}

