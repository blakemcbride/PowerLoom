//  -*- Mode: C++ -*-

// taxonomies.hh

/*
+---------------------------- BEGIN LICENSE BLOCK ---------------------------+
|                                                                            |
| Version: MPL 1.1/GPL 2.0/LGPL 2.1                                          |
|                                                                            |
| The contents of this file are subject to the Mozilla Public License        |
| Version 1.1 (the "License"); you may not use this file except in           |
| compliance with the License. You may obtain a copy of the License at       |
| http://www.mozilla.org/MPL/                                                |
|                                                                            |
| Software distributed under the License is distributed on an "AS IS" basis, |
| WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License   |
| for the specific language governing rights and limitations under the       |
| License.                                                                   |
|                                                                            |
| The Original Code is the STELLA Programming Language.                      |
|                                                                            |
| The Initial Developer of the Original Code is                              |
| UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
| 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
|                                                                            |
| Portions created by the Initial Developer are Copyright (C) 1996-2023      |
| the Initial Developer. All Rights Reserved.                                |
|                                                                            |
| Contributor(s):                                                            |
|                                                                            |
| Alternatively, the contents of this file may be used under the terms of    |
| either the GNU General Public License Version 2 or later (the "GPL"), or   |
| the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),   |
| in which case the provisions of the GPL or the LGPL are applicable instead |
| of those above. If you wish to allow use of your version of this file only |
| under the terms of either the GPL or the LGPL, and not to allow others to  |
| use your version of this file under the terms of the MPL, indicate your    |
| decision by deleting the provisions above and replace them with the notice |
| and other provisions required by the GPL or the LGPL. If you do not delete |
| the provisions above, a recipient may use your version of this file under  |
| the terms of any one of the MPL, the GPL or the LGPL.                      |
|                                                                            |
+---------------------------- END LICENSE BLOCK -----------------------------+
*/



namespace stella {

// Global declarations:
extern int oNUMBERING_INTERVALo;
extern int MARKER_LABEL;
extern int DELETED_LABEL;
extern DECLARE_STELLA_SPECIAL(oTAXONOMY_POSTORDER_NUMBERo, int );

// Function signatures:
boolean taxonomyRootP(TaxonomyNode* node);
void addTaxonomyRoot(TaxonomyGraph* graph, TaxonomyNode* root);
void removeTaxonomyRoot(TaxonomyGraph* graph, TaxonomyNode* root);
void updateTaxonomyRoots(TaxonomyGraph* graph, TaxonomyNode* node);
TaxonomyNode* createTaxonomyNode(TaxonomyGraph* graph, TaxonomyNode* node, Object* nativeobject, boolean rootP);
void addTaxonomyNode(TaxonomyGraph* graph, TaxonomyNode* node, boolean rootP);
void removeTaxonomyNode(TaxonomyGraph* graph, TaxonomyNode* node);
void createTaxonomyLink(TaxonomyGraph* graph, TaxonomyNode* parent, TaxonomyNode* child);
void linkTaxonomyNodes(TaxonomyGraph* graph, TaxonomyNode* parent, TaxonomyNode* child);
void incrementallyLinkTaxonomyNodes(TaxonomyGraph* graph, TaxonomyNode* parent, TaxonomyNode* child);
Interval* createNextPostorderInterval(TaxonomyGraph* graph);
Interval* allocateIntervalForNewLeafNode(TaxonomyNode* parent);
void unlinkTaxonomyNodes(TaxonomyGraph* graph, TaxonomyNode* parent, TaxonomyNode* child);
void incrementallyUnlinkTaxonomyNodes(TaxonomyGraph* graph, TaxonomyNode* parent, TaxonomyNode* child);
Iterator* allTaxonomyNodes(TaxonomyGraph* graph);
boolean allTaxonomyNodesNextP(AllPurposeIterator* self);
TaxonomyNode* findTaxonomyNode(TaxonomyGraph* graph, int label);
boolean labeledTaxonomyNodeP(TaxonomyNode* node);
void clearTaxonomyNode(TaxonomyNode* node);
void initializeTaxonomyNode(TaxonomyNode* node);
void helpClearTaxonomyGraph(TaxonomyNode* node);
void clearTaxonomyGraph(TaxonomyGraph* graph);
void initializeTaxonomyGraph(TaxonomyGraph* graph);
int helpCreateTaxonomyTreeIntervals(TaxonomyNode* self);
void createTaxonomyTreeIntervals(TaxonomyGraph* graph);
boolean subintervalOfP(Interval* subinterval, Interval* superinterval);
Interval* mergeIntervals(Interval* leftinterval, Interval* rightinterval);
Cons* allTaxonomyNodeIntervals(TaxonomyNode* node);
Interval* internTaxonomyNodeInterval(TaxonomyNode* node, int lowerbound, int upperbound);
void addTaxonomyNodeInterval(TaxonomyNode* node, Interval* interval);
void removeTaxonomyNodeInterval(TaxonomyNode* node, Interval* interval);
boolean adjoinTaxonomyNodeIntervalP(TaxonomyNode* node, Interval* interval);
void propagateForeignInterval(TaxonomyNode* node, Interval* interval);
void uncomputeTotalAncestors(TaxonomyNode* node);
void helpComputeTotalAncestors(TaxonomyNode* node);
void computeTotalAncestors(TaxonomyNode* node);
void createTaxonomySpanningTree(TaxonomyGraph* graph, TaxonomyNode* node);
void createTaxonomySpanningForest(TaxonomyGraph* graph);
void finalizeTaxonomyGraph(TaxonomyGraph* graph);
void finalizeTaxonomyGraphNonincrementally(TaxonomyGraph* graph);
boolean taxonomySubnodeOfP(TaxonomyNode* subNode, TaxonomyNode* superNode);
boolean slowTaxonomySubnodeOfP(TaxonomyNode* subnode, TaxonomyNode* supernode);
void printTaxonomyTree(TaxonomyNode* node, int indent, OutputStream* stream);
void printTaxonomyGraph(TaxonomyGraph* graph, OutputStream* stream);
void printTaxonomySpanningTree(TaxonomyNode* node, int indent, OutputStream* stream);
void printTaxonomySpanningForest(TaxonomyGraph* graph, OutputStream* stream);
void startupTaxonomies();

// Auxiliary global declarations:
extern Symbol* SYM_TAXONOMIES_STELLA_STARTUP_TAXONOMIES;
extern Symbol* SYM_TAXONOMIES_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
