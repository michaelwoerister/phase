
Phase
=====
In the *phase* project I am trying to explore a programming model for games and other cyclically updated simulation. My hope is that this model makes reasoning about game logic simpler. At the same time the model should lend itself well for parallelized execution.

## The Programming Model
The basic principle of a *phase* program is the separation of 
1. making decisions about how an object's state should change and
2. actually applying those state changes to the object.

This way an object can safely read the state of any other object while making decisions about its own state changes. The state of the simulated world, so to say, is constant during decision making and every object has the same view of it. Since objects only have a readonly view of the simulation state during decision making, this process can be performed in parallel for all objects. Pending object state changes are collected on a per-thread basis, thus not requiring any synchronization. As every object is only allowed to mutate its own state, no synchronization is needed for applying changes in the write phase either. Consequently, the whole update algorithm can be implemented lock-free and scales to as many CPU cores as there are objects in the simulation.

## How is this different from Software Transactional Memory?
Software Transactional Memory (STM) is a technique provides much of same benefits as the approach described above. If the update of an object is run as a transaction, it is guaranteed to have see a consistent state of the simulation---even if all updates were run concurrently. An STM implementation usually uses optimistic locking to provide this feature. That is, it assumes that it's reads are consistent during the update. When finished it asserts that this was actually the case. If true, the transaction is committed and the changes it made become globally visible. If false, the transaction is aborted---meaning no pending changes are actually performed---and retried at a later point in time.

This is very similar to what's done in *phase*, albeit with some differences:
* In *phase* all updates conceptually occur in parallel, at the same point in time. In constrast to that STM provides a way of conceptually serializing concurrent actions on some shared state. That is, modifications to the state are always put into some order, they happen at different points in time.
In practice this means that the following code segment will have different a semantic in *phase* and in an STM system:

    var x = 0
    var y = 1
    
    x.update  
    {
      x = y 
    }
    
    y.update  
    {
      y = x 
    }

In *phase* **x** and **y** will habe swapped their values. In STM, either both will be 0 or 1.

* TODO: simpler synchronization
* TODO: No rollback or conflicts

## How is this different from *Concurrent Revisions*?
TODO. [Concurrent Revisions](http://research.microsoft.com/en-us/projects/revisions/)