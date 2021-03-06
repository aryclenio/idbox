//Get Firebase Started
var config = {
  apiKey: "AIzaSyCSteal3DSLrenQgQFaWr-BHZKCl9kHl8I",
  authDomain: "idbox-76d4e.firebaseapp.com",
  databaseURL: "https://idbox-76d4e.firebaseio.com",
  projectId: "idbox-76d4e",
  storageBucket: "idbox-76d4e.appspot.com",
  messagingSenderId: "708708640728"
  };
  firebase.initializeApp(config);

  //Creating a Firebase Reference

document.getElementById('contactForm').addEventListener('submit', submitForm);

//Submit Form
function submitForm(e){
    e.preventDefault();
    var id = document.getElementById('id').value;
    var name = document.getElementById('name').value;
    var email = document.getElementById('email').value;
    var mat = document.getElementById('mat').value;
    

    saveMessage(id, name, email, mat);
    alert("Aluno Cadastrado com Sucesso");
    document.getElementById('contactForm').reset();
}
//Read files from DB
firebase.database().ref().child("cod").on("value", snap =>{
  var cod = snap.val();
  document.getElementById('id').value = cod;
});

//Saving the form
function saveMessage(id, name, email, mat){
    firebase.database().ref('id/'+id).set({
       a_Presente: "Nao",
       b_Matricula: mat,
       c_Nome: name,
       d_Email: email,
       e_Contagem: "0",
       f_Ultimo: "--/--/--"
    });
}




