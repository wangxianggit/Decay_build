Algorithm for event build and decay search in nuclear physics using double
side silicon detectors.

With the use of double side strip silicon detector, standard positionand- time correlation method has 
been applied to filter out the decay path efficiently.

tsort: event build, time windows is 500ns, event include signals of Mwpc, DSSD,Ge,Veto Si.
First the recorded events were sorted according to their timestamp, then an 500ns time window was applied to
the search of correlation signals.

decay: decay search, time windows depend on the half-life of interest species. The Mwpc energy was used to
distinguish decay event and heavy ion. The heavy ion corrospond to large Mwpc energy. Once a heavy ion implanted 
into DSSD was detected, the decay search was carried out through out the time window. 