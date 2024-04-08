//  -*- Mode: Java -*-
//
// PLDB.java

/*--------------------------------------------------------------------------+
 |                                                                          |
 |  Copyright (C) UNIVERSITY OF SOUTHERN CALIFORNIA, 2004-2019              |
 |  University of Southern California, Information Sciences Institute       |
 |  4676 Admiralty Way                                                      |
 |  Marina Del Rey, California 90292                                        |
 |                                                                          |
 |  This software was developed under the terms and conditions of Contract  |
 |  No. N00014-94-C-0245 between the Defense Advanced Research Projects     |
 |  Agency and the University of Southern California, Information Sciences  | 
 |  Institute.  Use and distribution of this software is further subject    |
 |  to the provisions of that contract and any other agreements developed   |
 |  between the user of the software and the University of Southern         |
 |  California, Information Sciences Institute.  It is supplied "AS IS",    |
 |  without any warranties of any kind.  It is furnished only on the basis  |
 |  that any party who receives it indemnifies and holds harmless the       |
 |  parties who furnish and originate it against any claims, demands, or    |
 |  liabilities connected with using it, furnishing it to others or         |
 |  providing it to a third party.  THIS NOTICE MUST NOT BE REMOVED FROM    |
 |  THE SOFTWARE, AND IN THE EVENT THAT THE SOFTWARE IS DIVIDED, IT SHOULD  |
 |  BE ATTACHED TO EVERY PART.                                              |
 |                                                                          |
 +--------------------------------------------------------------------------*/

// Version: $Id$

package edu.isi.powerloom.rdbms;

import edu.isi.stella.Stella;
import edu.isi.powerloom.logic.*;

public class PLDB {

  /** Main PowerLoom Database entry point for Java.
   *  Performs initialization of subsystems and then starts
   *  an interactive listener.
   *
   * @param args is ignored.
   */
  public static void main(String[] args) {
    initialize();
    Stella.string_changeContext("PL-USER");
    Logic.powerloom();
  }

  /** Initialize PowerLoom by starting up the required systems
   *  for using PowerLoom with a database system.
   */
  public static void initialize () {
    System.out.println("Initializing PowerLoom + RDBMS...");
    StartupRdbmsSystem.startupRdbmsSystem();
  }
}
