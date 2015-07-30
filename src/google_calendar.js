// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    send_next_event("For now", "Please wait")
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!');
  }                     
);

function send_next_event(time, event){
  // Assemble dictionary using our keys
  var dictionary = {
    'TIME': time,
    'EVENT': event
  };
  
  // Send to Pebble
  Pebble.sendAppMessage(dictionary,
    function(e) {
      console.log('Next event info sent to Pebble successfully!');
    },
    function(e) {
      console.log('Error sending next event info to Pebble!');
    }
  );
}