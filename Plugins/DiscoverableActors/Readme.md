## Unreal Engine RPC (Remote Procedure Call) Functions


RPC functions facilitate communication between server and client machines in a networked game. Here's how it works with different scenarios:

### Client RPC Function
When called on the server, it's executed on the client that owns the specific instance of the actor. Scenarios:

- **Player Controller:** If the RPC is part of a player controller class, the owning client corresponds to that player. The function will execute only on the client that controls that player.
- **Actors Owned by a Player:** If part of an actor owned by a player controller (e.g., a character or weapon), the function will execute only on the client that controls the corresponding player.
- **Other Actors:** If part of an actor without a specific owning client (e.g., a non-player-controlled enemy), calling a client RPC on it won't execute the function on any clients.

To define or redefine ownership, call `SetOwner` on the Server.

### Server RPC Function or Event
Called/sent only to the server and can only be invoked from a client. It won’t be executed on any Client machine.

### Multicast RPC
Can only be called on the server. It will be called not only for the owning client of the actor but also on every client's machines where the same actor is instantiated and replicated.

## About the Plugin
The plugin works in the Legacy way, overriding the `IsNetRelevantFor` function of the Actor class.
In order to make an Actor discoverable, you need to inherit from the `ADiscoverableActor` class.

`UDiscoverableActorsSubsystem` is a WorldSubsystem with 2 main functions to control the discovery of Actors:
- `MakeActorsReplicatedForPlayer` - makes the Actors discoverable for a specific PlayerController
- `MakeActorsNotReplicatedForPlayer` - makes the Actors not discoverable for a specific PlayerController

I have commented out part of code that can listen for GameplayMessaging events and call the above functions.
You can find the code in the `DiscoverableActorsSubsystem.cpp` file.
Here is the plugin for messaging that you can use. It is made buy Epic and is shipping with Lyra Sample: https://github.com/imnazake/gameplay-message-router
It might help you decouple your code in general and between the server and the client specifically.
