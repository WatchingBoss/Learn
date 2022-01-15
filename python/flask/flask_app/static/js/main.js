function translation(destination, postId) {
  let bodyJson = {
    message: "This is just text",
    post_id: postId
  };

  fetch("/translate", {
    method: 'post',
    body: JSON.stringify(bodyJson),
    headers: new Headers({
      'content-type': 'application/json'
    })
  }).then((response) => {
    if (response.status !== 200){
      console.log(`Looks like there was a problem. Status code: ${response.status}`);
      return;
    }
    response.json().then(function (data){
      document.getElementById(destination).textContent = data.text;
    });
  }).catch((error) => {
    console.log("Fetch error" + error);
  })
}
