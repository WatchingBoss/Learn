function validate(){
    let v1 = document.getElementById("num1");
    let v2 = document.getElementById("num2");
    let output = document.getElementById("output");

    if(v1.value !== "" && v2.value !== "")
        if(v1.value === v2.value){
            output.innerHTML = "Strings similar. Good";
            return true;
        }

    output.innerHTML = "Second string isn't same!";
}