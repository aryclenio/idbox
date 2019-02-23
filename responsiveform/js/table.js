(function() {
  const config = {
    apiKey: "AIzaSyCSteal3DSLrenQgQFaWr-BHZKCl9kHl8I",
    authDomain: "idbox-76d4e.firebaseapp.com",
    databaseURL: "https://idbox-76d4e.firebaseio.com",
    projectId: "idbox-76d4e",
    storageBucket: "idbox-76d4e.appspot.com",
    messagingSenderId: "708708640728"

  };

  firebase.initializeApp(config);
  const bigTextEvaluationStudents = document.getElementById('id');
  const dbBigTextEvaluationStudentsRef = firebase.database().ref().child('id');
  dbBigTextEvaluationStudentsRef.on('value', snap => bigTextEvaluationStudents.innerText = snap.val());

  var table = document.querySelector('#table1 tbody');
  const dbEvaluationStudentsRef = firebase.database().ref().child('id');
  dbEvaluationStudentsRef.on('value', snap => {
    while(table.hasChildNodes()) {
		    table.removeChild(table.firstChild);
	  }

    var id = snap.val();
    for(var i in id) {
      var row = table.insertRow(-1);
      for(var j in id[i]) {
				cell = row.insertCell(-1);
				cell.innerHTML = id[i][j];
			}
		}
  });
}());
