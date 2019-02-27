 // Initialize Firebase
 var config = {
    
    apiKey: "AIzaSyCSteal3DSLrenQgQFaWr-BHZKCl9kHl8I",
    authDomain: "idbox-76d4e.firebaseapp.com",
    databaseURL: "https://idbox-76d4e.firebaseio.com",
    projectId: "idbox-76d4e",
    storageBucket: "idbox-76d4e.appspot.com",
    messagingSenderId: "708708640728"
  };
  firebase.initializeApp(config);
  firebase.auth().signOut();
  const txtEmail = document.getElementById('txtEmail');
  const btnSingUp = document.getElementById('btnSingUp');
  const txtPassword = document.getElementById('txtPassword');
  const confirmetxtPassword = document.getElementById('confirmetxtPassword')

    //add um registro

    btnSingUp.addEventListener('click', e => {

      // pegando email e senha
      const email = txtEmail.value;
      const pass = txtPassword.value;
      const confirmepass = confirmetxtPassword.value; 
      const auth = firebase.auth();
  
      //Registrando no banco
      if(pass == confirmepass){
      const promise = auth.createUserWithEmailAndPassword(email,pass);
      }else{
        window.alert('Senhas diferentes, Digite novamente')
      }
      promise.catch(e =>window.alert(e.message));
    
    
    });
  
  
  
         //vericando em tempo real
     firebase.auth().onAuthStateChanged(firebaseUser => {
       if(firebaseUser){
         console.log(firebaseUser);
        
         window.location.href ='index.html';
         
       } else {
         console.log('nao cadastrado');
        
       }
  
   });