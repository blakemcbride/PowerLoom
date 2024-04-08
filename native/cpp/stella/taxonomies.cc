//  -*- Mode: C++ -*-

// taxonomies.cc

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

#include "stella/stella-system.hh"

namespace stella {

// Spacing between postorder numbers for nodes.  Allows limited
// incremental insertions without having to renumber the whole graph.
int oNUMBERING_INTERVALo = 100;

boolean taxonomyRootP(TaxonomyNode* node) {
  // Return `true' if `node' is a taxonomy root node.
  return (node->parents == NIL);
}

void addTaxonomyRoot(TaxonomyGraph* graph, TaxonomyNode* root) {
  // Add `root' as a root node to `graph'.  Only do this if
  // `root' does not have any parents and is not a `graph' root already.
  graph->roots->insertNew(root);
}

void removeTaxonomyRoot(TaxonomyGraph* graph, TaxonomyNode* root) {
  // Remove `root' from `graph's root nodes.
  if (!(root->label == DELETED_LABEL)) {
    graph->roots->remove(root);
  }
}

void updateTaxonomyRoots(TaxonomyGraph* graph, TaxonomyNode* node) {
  // Update `graph's roots according to `node's current state.
  if (node->parents == NIL) {
    addTaxonomyRoot(graph, node);
  }
  else {
    removeTaxonomyRoot(graph, node);
  }
}

TaxonomyNode* createTaxonomyNode(TaxonomyGraph* graph, TaxonomyNode* node, Object* nativeobject, boolean rootP) {
  // Link the taxonomy node `node' to `nativeObject' and add it
  // to `graph'.  If it is `null', a new node will be created.  Mark it as a root
  // node if `root?' is `true'.  Return the node.
  if (!((boolean)(node))) {
    { TaxonomyNode* self000 = newTaxonomyNode();

      self000->nativeObject = nativeobject;
      node = self000;
    }
  }
  else {
    initializeTaxonomyNode(node);
    node->nativeObject = nativeobject;
  }
  addTaxonomyNode(graph, node, rootP);
  return (node);
}

void addTaxonomyNode(TaxonomyGraph* graph, TaxonomyNode* node, boolean rootP) {
  // Add `node' to `graph'.  Mark it as a root node if `root?'
  // is `true'.  Even though this is part of the API, it should rarely be needed,
  // since `create-taxonomy-node' does everything that's necessary.
  if (rootP) {
    addTaxonomyRoot(graph, node);
  }
  graph->numberOfNodes = graph->numberOfNodes + 1;
}

void removeTaxonomyNode(TaxonomyGraph* graph, TaxonomyNode* node) {
  // Remove `node' from `graph' and disconnect incident links.
  { Cons* parentscopy = copyConsList(node->parents);
    Cons* childrencopy = copyConsList(node->children);

    { TaxonomyNode* parent = NULL;
      Cons* iter000 = parentscopy;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        parent = ((TaxonomyNode*)(iter000->value));
        unlinkTaxonomyNodes(graph, parent, node);
      }
    }
    { TaxonomyNode* child = NULL;
      Cons* iter001 = childrencopy;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        child = ((TaxonomyNode*)(iter001->value));
        unlinkTaxonomyNodes(graph, node, child);
      }
    }
    node->intervals = NIL;
    node->nativeObject = NULL;
    node->deletedPSetter(true);
    removeTaxonomyRoot(graph, node);
    graph->numberOfNodes = graph->numberOfNodes - 1;
  }
}

void createTaxonomyLink(TaxonomyGraph* graph, TaxonomyNode* parent, TaxonomyNode* child) {
  removeTaxonomyRoot(graph, child);
  child->parents = cons(parent, child->parents);
  parent->children = cons(child, parent->children);
}

void linkTaxonomyNodes(TaxonomyGraph* graph, TaxonomyNode* parent, TaxonomyNode* child) {
  // Cross-link `parent' and `child' in `graph'.
  // IMPORTANT: This will automatically insert a backlink from `child' to
  // `parent', so, for maximum efficiency it should not be called a second time
  // with the arguments reversed.
  if (parent->children->membP(child)) {
    return;
  }
  if (graph->incrementalModeP) {
    graph->addedLinks->push(cons(parent, cons(child, NIL)));
  }
  else {
    createTaxonomyLink(graph, parent, child);
  }
}

void incrementallyLinkTaxonomyNodes(TaxonomyGraph* graph, TaxonomyNode* parent, TaxonomyNode* child) {
  if (parent->children->membP(child)) {
    return;
  }
  createTaxonomyLink(graph, parent, child);
  { Interval* interval = NULL;
    boolean parentexistsP = ((boolean)(parent->initialInterval));
    boolean childexistsP = ((boolean)(child->initialInterval));

    if (childexistsP) {
      if (!parentexistsP) {
        interval = createNextPostorderInterval(graph);
        parent->initialInterval = interval;
        parent->label = interval->upperBound;
        addTaxonomyNodeInterval(parent, interval);
      }
      { Interval* interval = NULL;
        Cons* iter000 = child->intervals;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          interval = ((Interval*)(iter000->value));
          propagateForeignInterval(parent, interval);
        }
      }
    }
    else {
      if (!parentexistsP) {
        interval = createNextPostorderInterval(graph);
        parent->initialInterval = interval;
        parent->label = interval->upperBound;
        addTaxonomyNodeInterval(parent, interval);
      }
      interval = allocateIntervalForNewLeafNode(parent);
      if (!((boolean)(interval))) {
        if (graph->renumberIfOutOfNumbersP) {
          finalizeTaxonomyGraphNonincrementally(graph);
          return;
        }
        interval = createNextPostorderInterval(graph);
      }
      child->initialInterval = interval;
      child->label = interval->upperBound;
      addTaxonomyNodeInterval(child, interval);
      parent->treeChildren = parent->treeChildren->concatenate(cons(child, NIL), 0);
      propagateForeignInterval(parent, interval);
    }
  }
}

Interval* createNextPostorderInterval(TaxonomyGraph* graph) {
  graph->numberOfForeignIntervalNodes = graph->numberOfForeignIntervalNodes + 1;
  { Interval* newinterval = newInterval();

    newinterval->lowerBound = graph->largestPostorderNumber + 1;
    newinterval->upperBound = graph->largestPostorderNumber + oNUMBERING_INTERVALo;
    graph->largestPostorderNumber = newinterval->upperBound;
    return (newinterval);
  }
}

Interval* allocateIntervalForNewLeafNode(TaxonomyNode* parent) {
  { Interval* parentinterval = parent->initialInterval;

    if (parent->treeChildren == NIL) {
      if (parentinterval->lowerBound == parentinterval->upperBound) {
        return (NULL);
      }
      { Interval* self000 = newInterval();

        self000->lowerBound = parentinterval->lowerBound;
        self000->upperBound = stella::floor((parentinterval->lowerBound + parentinterval->upperBound) / 2.0);
        { Interval* value000 = self000;

          return (value000);
        }
      }
    }
    { TaxonomyNode* rightchild = ((TaxonomyNode*)(parent->treeChildren->last()));
      Interval* rightchildinterval = rightchild->initialInterval;

      if (rightchildinterval->upperBound >= (parentinterval->upperBound - 1)) {
        return (NULL);
      }
      { Interval* self001 = newInterval();

        self001->lowerBound = rightchildinterval->upperBound + 1;
        self001->upperBound = ceiling((parentinterval->upperBound + rightchildinterval->upperBound) / 2.0);
        { Interval* value001 = self001;

          return (value001);
        }
      }
    }
  }
}

void unlinkTaxonomyNodes(TaxonomyGraph* graph, TaxonomyNode* parent, TaxonomyNode* child) {
  // Remove link between `parent' and `child'.
  if (!parent->children->membP(child)) {
    return;
  }
  if (graph->incrementalModeP) {
    graph->incrementalModeP = false;
  }
  parent->children = parent->children->remove(child);
  parent->treeChildren = parent->treeChildren->remove(child);
  child->parents = child->parents->remove(parent);
  updateTaxonomyRoots(graph, child);
}

void incrementallyUnlinkTaxonomyNodes(TaxonomyGraph* graph, TaxonomyNode* parent, TaxonomyNode* child) {
  {
    graph = graph;
    parent = parent;
    child = child;
  }
  throw *newStellaException("incrementally-unlink-taxonomy-nodes: Rewrite me!");
}

Iterator* allTaxonomyNodes(TaxonomyGraph* graph) {
  // Given a taxonomy `graph' that has been finalized,
  // return an iterator that generates all the graph's nodes.
  { AllPurposeIterator* self000 = newAllPurposeIterator();

    self000->iteratorObject = graph->roots->copy();
    self000->iteratorNextCode = ((cpp_function_code)(&allTaxonomyNodesNextP));
    { AllPurposeIterator* value000 = self000;

      return (value000);
    }
  }
}

boolean allTaxonomyNodesNextP(AllPurposeIterator* self) {
  { List* roots = ((List*)(self->iteratorObject));

    if (roots->emptyP()) {
      return (false);
    }
    self->value = ((TaxonomyNode*)(roots->pop()));
    { TaxonomyNode* child = NULL;
      Cons* iter000 = ((TaxonomyNode*)(self->value))->treeChildren;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        child = ((TaxonomyNode*)(iter000->value));
        roots->push(child);
      }
    }
    return (true);
  }
}

TaxonomyNode* findTaxonomyNode(TaxonomyGraph* graph, int label) {
  // Return some node in `graph' with label `label'.
  { TaxonomyNode* node = NULL;
    Iterator* iter000 = allTaxonomyNodes(graph);

    for (; iter000->nextP(); ) {
      node = ((TaxonomyNode*)(iter000->value));
      if (node->label == label) {
        return (node);
      }
    }
  }
  return (NULL);
}

// Dummy label used for marking a node
int MARKER_LABEL = -99;

// Label used for marking deleted nodes
int DELETED_LABEL = -99;

boolean labeledTaxonomyNodeP(TaxonomyNode* node) {
  return (node->label != NULL_INTEGER);
}

boolean TaxonomyNode::deletedP() {
  { TaxonomyNode* self = this;

    return (self->label == DELETED_LABEL);
  }
}

boolean TaxonomyNode::deletedPSetter(boolean value) {
  { TaxonomyNode* self = this;

    if (value) {
      self->label = DELETED_LABEL;
    }
    else {
      self->label = NULL_INTEGER;
    }
    return (value);
  }
}

void clearTaxonomyNode(TaxonomyNode* node) {
  // Clear all taxonomy-graph-specific information of `node',
  // but retain information about the native object and associated links.
  node->label = NULL_INTEGER;
  node->intervals = NIL;
  node->initialInterval = NULL;
  node->firstIntervalLowerBound = -1;
  node->firstIntervalUpperBound = -1;
  node->treeChildren = NIL;
  node->totalAncestors = 1;
}

void initializeTaxonomyNode(TaxonomyNode* node) {
  // Completely clear and initialize `node'.
  clearTaxonomyNode(node);
  node->parents = NIL;
  node->children = NIL;
  node->nativeObject = NULL;
}

void helpClearTaxonomyGraph(TaxonomyNode* node) {
  if (node->label != NULL_INTEGER) {
    clearTaxonomyNode(node);
    { TaxonomyNode* child = NULL;
      Cons* iter000 = node->children;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        child = ((TaxonomyNode*)(iter000->value));
        helpClearTaxonomyGraph(child);
      }
    }
  }
}

void clearTaxonomyGraph(TaxonomyGraph* graph) {
  // Clear all taxonomy-graph-specific information of `graph',
  // but retain information about the native network and associated links.
  { TaxonomyNode* root = NULL;
    Cons* iter000 = graph->roots->removeDeletedMembers()->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      root = ((TaxonomyNode*)(iter000->value));
      helpClearTaxonomyGraph(root);
    }
  }
  graph->incrementalModeP = false;
  graph->numberOfForeignIntervalNodes = 0;
  graph->brokenLinks->clear();
}

void initializeTaxonomyGraph(TaxonomyGraph* graph) {
  // Completely clear the taxonomy graph `graph'.
  // NOTE: Any nodes associated with `graph' will not be cleared.  If they are
  // to be reused, they have to be cleared with `initialize-taxonomy-node'.
  graph->incrementalModeP = false;
  graph->renumberIfOutOfNumbersP = false;
  graph->largestPostorderNumber = 0;
  graph->numberOfNodes = 0;
  graph->numberOfForeignIntervalNodes = 0;
  graph->renumberRatio = 0.1;
  graph->roots = newList();
  graph->brokenLinks = newList();
  graph->addedLinks = newList();
  graph->removedLinks = newList();
}

DEFINE_STELLA_SPECIAL(oTAXONOMY_POSTORDER_NUMBERo, int , NULL_INTEGER);

int helpCreateTaxonomyTreeIntervals(TaxonomyNode* self) {
  { int minchildlabel = NULL_INTEGER;
    int mylabel = NULL_INTEGER;
    int prevpostnumber = oTAXONOMY_POSTORDER_NUMBERo;

    if (!(self->treeChildren == NIL)) {
      minchildlabel = helpCreateTaxonomyTreeIntervals(((TaxonomyNode*)(self->treeChildren->value)));
    }
    { TaxonomyNode* child = NULL;
      Cons* iter000 = self->treeChildren->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        child = ((TaxonomyNode*)(iter000->value));
        helpCreateTaxonomyTreeIntervals(child);
      }
    }
    oTAXONOMY_POSTORDER_NUMBERo = oTAXONOMY_POSTORDER_NUMBERo + oNUMBERING_INTERVALo;
    mylabel = oTAXONOMY_POSTORDER_NUMBERo;
    if (self->treeChildren == NIL) {
      minchildlabel = prevpostnumber + 1;
    }
    self->initialInterval = internTaxonomyNodeInterval(self, minchildlabel, mylabel);
    self->label = mylabel;
    return (minchildlabel);
  }
}

void createTaxonomyTreeIntervals(TaxonomyGraph* graph) {
  { 
    BIND_STELLA_SPECIAL(oTAXONOMY_POSTORDER_NUMBERo, int, 0);
    { TaxonomyNode* root = NULL;
      Cons* iter000 = graph->roots->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        root = ((TaxonomyNode*)(iter000->value));
        helpCreateTaxonomyTreeIntervals(root);
      }
    }
    graph->largestPostorderNumber = oTAXONOMY_POSTORDER_NUMBERo;
  }
}

boolean Interval::memberP(int n) {
  { Interval* interval = this;

    return ((n >= interval->lowerBound) &&
        (n <= interval->upperBound));
  }
}

boolean subintervalOfP(Interval* subinterval, Interval* superinterval) {
  return ((subinterval->upperBound <= superinterval->upperBound) &&
      (subinterval->lowerBound >= superinterval->lowerBound));
}

Interval* mergeIntervals(Interval* leftinterval, Interval* rightinterval) {
  { Interval* self000 = newInterval();

    self000->lowerBound = leftinterval->lowerBound;
    self000->upperBound = rightinterval->upperBound;
    { Interval* value000 = self000;

      return (value000);
    }
  }
}

Cons* allTaxonomyNodeIntervals(TaxonomyNode* node) {
  return (node->intervals);
}

Interval* internTaxonomyNodeInterval(TaxonomyNode* node, int lowerbound, int upperbound) {
  { Interval* self000 = newInterval();

    self000->lowerBound = lowerbound;
    self000->upperBound = upperbound;
    { Interval* interval = self000;

      addTaxonomyNodeInterval(node, interval);
      return (interval);
    }
  }
}

void addTaxonomyNodeInterval(TaxonomyNode* node, Interval* interval) {
  node->intervals = cons(interval, node->intervals);
  node->firstIntervalLowerBound = interval->lowerBound;
  node->firstIntervalUpperBound = interval->upperBound;
}

void removeTaxonomyNodeInterval(TaxonomyNode* node, Interval* interval) {
  { Cons* intervals = node->intervals;

    intervals = node->intervals = intervals->remove(interval);
    if (intervals == NIL) {
      node->firstIntervalLowerBound = -1;
      node->firstIntervalUpperBound = -1;
    }
    else {
      node->firstIntervalLowerBound = ((Interval*)(intervals->value))->lowerBound;
      node->firstIntervalUpperBound = ((Interval*)(intervals->value))->upperBound;
    }
  }
}

boolean adjoinTaxonomyNodeIntervalP(TaxonomyNode* node, Interval* interval) {
  { Cons* intervalstoremove = NIL;

    { Interval* inT = NULL;
      Cons* iter000 = node->intervals;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        inT = ((Interval*)(iter000->value));
        if (inT->lowerBound < interval->lowerBound) {
          if (inT->upperBound >= interval->upperBound) {
            return (false);
          }
          else {
            if (interval->lowerBound <= (inT->upperBound + 1)) {
              removeTaxonomyNodeInterval(node, inT);
              adjoinTaxonomyNodeIntervalP(node, mergeIntervals(inT, interval));
              return (true);
            }
          }
        }
        else {
          if (interval->upperBound >= inT->upperBound) {
            intervalstoremove = cons(inT, intervalstoremove);
          }
          else {
            if (inT->lowerBound <= (interval->upperBound + 1)) {
              removeTaxonomyNodeInterval(node, inT);
              adjoinTaxonomyNodeIntervalP(node, mergeIntervals(interval, inT));
              return (true);
            }
          }
        }
      }
    }
    { Object* inT = NULL;
      Cons* iter001 = intervalstoremove;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        inT = iter001->value;
        removeTaxonomyNodeInterval(node, ((Interval*)(inT)));
      }
    }
    addTaxonomyNodeInterval(node, interval);
    return (true);
  }
}

void propagateForeignInterval(TaxonomyNode* node, Interval* interval) {
  if (node->marker == interval) {
    return;
  }
  node->marker = interval;
  if (adjoinTaxonomyNodeIntervalP(node, interval)) {
    { TaxonomyNode* parent = NULL;
      Cons* iter000 = node->parents;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        parent = ((TaxonomyNode*)(iter000->value));
        propagateForeignInterval(parent, interval);
      }
    }
  }
}

void uncomputeTotalAncestors(TaxonomyNode* node) {
  if (node->totalAncestors < 0) {
    return;
  }
  node->totalAncestors = -1;
  { TaxonomyNode* child = NULL;
    Cons* iter000 = node->children;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      child = ((TaxonomyNode*)(iter000->value));
      uncomputeTotalAncestors(child);
    }
  }
}

void helpComputeTotalAncestors(TaxonomyNode* node) {
  if (node->totalAncestors >= 0) {
    return;
  }
  { int totalancestors = 0;
    int parentancestors = 0;

    { TaxonomyNode* parent = NULL;
      Cons* iter000 = node->parents;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        parent = ((TaxonomyNode*)(iter000->value));
        parentancestors = parent->totalAncestors;
        if (parentancestors < 0) {
          return;
        }
        totalancestors = totalancestors + parentancestors;
      }
    }
    node->totalAncestors = totalancestors + 1;
    { TaxonomyNode* child = NULL;
      Cons* iter001 = node->children;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        child = ((TaxonomyNode*)(iter001->value));
        helpComputeTotalAncestors(child);
      }
    }
  }
}

void computeTotalAncestors(TaxonomyNode* node) {
  uncomputeTotalAncestors(node);
  helpComputeTotalAncestors(node);
}

void createTaxonomySpanningTree(TaxonomyGraph* graph, TaxonomyNode* node) {
  if (node->label != NULL_INTEGER) {
    return;
  }
  node->label = MARKER_LABEL;
  { TaxonomyNode* maxparent = NULL;
    int maxparentvalue = NULL_INTEGER;

    { TaxonomyNode* parent = NULL;
      Cons* iter000 = node->parents;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        parent = ((TaxonomyNode*)(iter000->value));
        if ((maxparentvalue == NULL_INTEGER) ||
            (parent->totalAncestors > maxparentvalue)) {
          maxparent = parent;
          maxparentvalue = parent->totalAncestors;
        }
      }
    }
    { TaxonomyNode* parent = NULL;
      Cons* iter001 = node->parents;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        parent = ((TaxonomyNode*)(iter001->value));
        if (parent == maxparent) {
          parent->treeChildren = cons(node, parent->treeChildren);
        }
        else {
          graph->brokenLinks->push(cons(parent, cons(node, NIL)));
        }
      }
    }
    { TaxonomyNode* child = NULL;
      Cons* iter002 = node->children;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        child = ((TaxonomyNode*)(iter002->value));
        createTaxonomySpanningTree(graph, child);
      }
    }
  }
}

void createTaxonomySpanningForest(TaxonomyGraph* graph) {
  clearTaxonomyGraph(graph);
  graph->incrementalModeP = false;
  { TaxonomyNode* root = NULL;
    Cons* iter000 = graph->roots->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      root = ((TaxonomyNode*)(iter000->value));
      computeTotalAncestors(root);
      createTaxonomySpanningTree(graph, root);
    }
  }
  createTaxonomyTreeIntervals(graph);
  { Cons* link = NULL;
    Cons* iter001 = graph->brokenLinks->theConsList;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      link = ((Cons*)(iter001->value));
      propagateForeignInterval(((TaxonomyNode*)(link->value)), ((TaxonomyNode*)(link->rest->value))->initialInterval);
    }
  }
  graph->brokenLinks->clear();
  graph->incrementalModeP = true;
}

void finalizeTaxonomyGraph(TaxonomyGraph* graph) {
  // Finalize the taxonomy graph `graph'.
  if (graph->incrementalModeP &&
      ((graph->numberOfNodes > 0) &&
       ((((double)(stella::integerMax(graph->numberOfForeignIntervalNodes, graph->addedLinks->length()))) / graph->numberOfNodes) < graph->renumberRatio))) {
    { Cons* link = NULL;
      Cons* iter000 = graph->addedLinks->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        link = ((Cons*)(iter000->value));
        incrementallyLinkTaxonomyNodes(graph, ((TaxonomyNode*)(link->value)), ((TaxonomyNode*)(link->rest->value)));
      }
    }
    graph->addedLinks->clear();
  }
  else {
    graph->incrementalModeP = false;
    { Cons* link = NULL;
      Cons* iter001 = graph->addedLinks->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        link = ((Cons*)(iter001->value));
        linkTaxonomyNodes(graph, ((TaxonomyNode*)(link->value)), ((TaxonomyNode*)(link->rest->value)));
      }
    }
    graph->addedLinks->clear();
    createTaxonomySpanningForest(graph);
  }
}

void finalizeTaxonomyGraphNonincrementally(TaxonomyGraph* graph) {
  graph->incrementalModeP = false;
  finalizeTaxonomyGraph(graph);
}

boolean taxonomySubnodeOfP(TaxonomyNode* subNode, TaxonomyNode* superNode) {
  // Return TRUE if `sub-node' is a descendant of `super-node'.
  { int subNodeLabel = subNode->label;

    { Interval* interval = NULL;
      Cons* iter000 = superNode->intervals;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        interval = ((Interval*)(iter000->value));
        if ((subNodeLabel >= interval->lowerBound) &&
            (subNodeLabel <= interval->upperBound)) {
          return (true);
        }
      }
    }
    return (false);
  }
}

boolean slowTaxonomySubnodeOfP(TaxonomyNode* subnode, TaxonomyNode* supernode) {
  if (subnode == supernode) {
    return (true);
  }
  { TaxonomyNode* parent = NULL;
    Cons* iter000 = subnode->parents;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      parent = ((TaxonomyNode*)(iter000->value));
      if (slowTaxonomySubnodeOfP(parent, supernode)) {
        return (true);
      }
    }
  }
  return (false);
}

void printTaxonomyTree(TaxonomyNode* node, int indent, OutputStream* stream) {
  { int i = NULL_INTEGER;
    int iter000 = 1;
    int upperBound000 = indent;
    boolean unboundedP000 = upperBound000 == NULL_INTEGER;

    for  (; unboundedP000 ||
              (iter000 <= upperBound000); 
          iter000 = iter000 + 1) {
      i = iter000;
      i = i;
      *(stream->nativeStream) << " ";
    }
  }
  *(stream->nativeStream) << node << std::endl;
  { TaxonomyNode* child = NULL;
    Cons* iter001 = node->children;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      child = ((TaxonomyNode*)(iter001->value));
      printTaxonomyTree(child, indent + 2, stream);
    }
  }
}

void printTaxonomyGraph(TaxonomyGraph* graph, OutputStream* stream) {
  { TaxonomyNode* root = NULL;
    Cons* iter000 = graph->roots->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      root = ((TaxonomyNode*)(iter000->value));
      printTaxonomyTree(root, 0, stream);
      *(stream->nativeStream) << std::endl;
    }
  }
}

void printTaxonomySpanningTree(TaxonomyNode* node, int indent, OutputStream* stream) {
  { int i = NULL_INTEGER;
    int iter000 = 1;
    int upperBound000 = indent;
    boolean unboundedP000 = upperBound000 == NULL_INTEGER;

    for  (; unboundedP000 ||
              (iter000 <= upperBound000); 
          iter000 = iter000 + 1) {
      i = iter000;
      i = i;
      *(stream->nativeStream) << " ";
    }
  }
  *(stream->nativeStream) << node << std::endl;
  { TaxonomyNode* child = NULL;
    Cons* iter001 = node->treeChildren;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      child = ((TaxonomyNode*)(iter001->value));
      printTaxonomySpanningTree(child, indent + 2, stream);
    }
  }
}

void printTaxonomySpanningForest(TaxonomyGraph* graph, OutputStream* stream) {
  { TaxonomyNode* root = NULL;
    Cons* iter000 = graph->roots->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      root = ((TaxonomyNode*)(iter000->value));
      printTaxonomySpanningTree(root, 0, stream);
      *(stream->nativeStream) << std::endl;
    }
  }
}

void startupTaxonomies() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SYM_TAXONOMIES_STELLA_STARTUP_TAXONOMIES = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TAXONOMIES", NULL, 0)));
      SYM_TAXONOMIES_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(4)) {
      oTAXONOMY_POSTORDER_NUMBERo = NULL_INTEGER;
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("TAXONOMY-ROOT?", "(DEFUN (TAXONOMY-ROOT? BOOLEAN) ((NODE TAXONOMY-NODE)) :DOCUMENTATION \"Return `true' if `node' is a taxonomy root node.\" :GLOBALLY-INLINE? TRUE (RETURN (EMPTY? (PARENTS NODE))))", ((cpp_function_code)(&taxonomyRootP)), NULL);
      defineFunctionObject("ADD-TAXONOMY-ROOT", "(DEFUN ADD-TAXONOMY-ROOT ((GRAPH TAXONOMY-GRAPH) (ROOT TAXONOMY-NODE)) :DOCUMENTATION \"Add `root' as a root node to `graph'.  Only do this if\n`root' does not have any parents and is not a `graph' root already.\" :PUBLIC? TRUE)", ((cpp_function_code)(&addTaxonomyRoot)), NULL);
      defineFunctionObject("REMOVE-TAXONOMY-ROOT", "(DEFUN REMOVE-TAXONOMY-ROOT ((GRAPH TAXONOMY-GRAPH) (ROOT TAXONOMY-NODE)) :DOCUMENTATION \"Remove `root' from `graph's root nodes.\" :PUBLIC? TRUE)", ((cpp_function_code)(&removeTaxonomyRoot)), NULL);
      defineFunctionObject("UPDATE-TAXONOMY-ROOTS", "(DEFUN UPDATE-TAXONOMY-ROOTS ((GRAPH TAXONOMY-GRAPH) (NODE TAXONOMY-NODE)) :DOCUMENTATION \"Update `graph's roots according to `node's current state.\" :PUBLIC? TRUE)", ((cpp_function_code)(&updateTaxonomyRoots)), NULL);
      defineFunctionObject("CREATE-TAXONOMY-NODE", "(DEFUN (CREATE-TAXONOMY-NODE TAXONOMY-NODE) ((GRAPH TAXONOMY-GRAPH) (NODE TAXONOMY-NODE) (NATIVEOBJECT OBJECT) (ROOT? BOOLEAN)) :DOCUMENTATION \"Link the taxonomy node `node' to `nativeObject' and add it\nto `graph'.  If it is `null', a new node will be created.  Mark it as a root\nnode if `root?' is `true'.  Return the node.\" :PUBLIC? TRUE)", ((cpp_function_code)(&createTaxonomyNode)), NULL);
      defineFunctionObject("ADD-TAXONOMY-NODE", "(DEFUN ADD-TAXONOMY-NODE ((GRAPH TAXONOMY-GRAPH) (NODE TAXONOMY-NODE) (ROOT? BOOLEAN)) :DOCUMENTATION \"Add `node' to `graph'.  Mark it as a root node if `root?'\nis `true'.  Even though this is part of the API, it should rarely be needed,\nsince `create-taxonomy-node' does everything that's necessary.\" :PUBLIC? TRUE)", ((cpp_function_code)(&addTaxonomyNode)), NULL);
      defineFunctionObject("REMOVE-TAXONOMY-NODE", "(DEFUN REMOVE-TAXONOMY-NODE ((GRAPH TAXONOMY-GRAPH) (NODE TAXONOMY-NODE)) :PUBLIC? TRUE :DOCUMENTATION \"Remove `node' from `graph' and disconnect incident links.\")", ((cpp_function_code)(&removeTaxonomyNode)), NULL);
      defineFunctionObject("CREATE-TAXONOMY-LINK", "(DEFUN CREATE-TAXONOMY-LINK ((GRAPH TAXONOMY-GRAPH) (PARENT TAXONOMY-NODE) (CHILD TAXONOMY-NODE)) :PUBLIC? TRUE)", ((cpp_function_code)(&createTaxonomyLink)), NULL);
      defineFunctionObject("LINK-TAXONOMY-NODES", "(DEFUN LINK-TAXONOMY-NODES ((GRAPH TAXONOMY-GRAPH) (PARENT TAXONOMY-NODE) (CHILD TAXONOMY-NODE)) :DOCUMENTATION \"Cross-link `parent' and `child' in `graph'.\nIMPORTANT: This will automatically insert a backlink from `child' to\n`parent', so, for maximum efficiency it should not be called a second time\nwith the arguments reversed.\" :PUBLIC? TRUE)", ((cpp_function_code)(&linkTaxonomyNodes)), NULL);
      defineFunctionObject("INCREMENTALLY-LINK-TAXONOMY-NODES", "(DEFUN INCREMENTALLY-LINK-TAXONOMY-NODES ((GRAPH TAXONOMY-GRAPH) (PARENT TAXONOMY-NODE) (CHILD TAXONOMY-NODE)))", ((cpp_function_code)(&incrementallyLinkTaxonomyNodes)), NULL);
      defineFunctionObject("CREATE-NEXT-POSTORDER-INTERVAL", "(DEFUN (CREATE-NEXT-POSTORDER-INTERVAL INTERVAL) ((GRAPH TAXONOMY-GRAPH)))", ((cpp_function_code)(&createNextPostorderInterval)), NULL);
      defineFunctionObject("ALLOCATE-INTERVAL-FOR-NEW-LEAF-NODE", "(DEFUN (ALLOCATE-INTERVAL-FOR-NEW-LEAF-NODE INTERVAL) ((PARENT TAXONOMY-NODE)))", ((cpp_function_code)(&allocateIntervalForNewLeafNode)), NULL);
      defineFunctionObject("UNLINK-TAXONOMY-NODES", "(DEFUN UNLINK-TAXONOMY-NODES ((GRAPH TAXONOMY-GRAPH) (PARENT TAXONOMY-NODE) (CHILD TAXONOMY-NODE)) :DOCUMENTATION \"Remove link between `parent' and `child'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unlinkTaxonomyNodes)), NULL);
      defineFunctionObject("INCREMENTALLY-UNLINK-TAXONOMY-NODES", "(DEFUN INCREMENTALLY-UNLINK-TAXONOMY-NODES ((GRAPH TAXONOMY-GRAPH) (PARENT TAXONOMY-NODE) (CHILD TAXONOMY-NODE)))", ((cpp_function_code)(&incrementallyUnlinkTaxonomyNodes)), NULL);
      defineFunctionObject("ALL-TAXONOMY-NODES", "(DEFUN (ALL-TAXONOMY-NODES (ITERATOR OF TAXONOMY-NODE)) ((GRAPH TAXONOMY-GRAPH)) :DOCUMENTATION \"Given a taxonomy `graph' that has been finalized,\nreturn an iterator that generates all the graph's nodes.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allTaxonomyNodes)), NULL);
      defineFunctionObject("ALL-TAXONOMY-NODES-NEXT?", "(DEFUN (ALL-TAXONOMY-NODES-NEXT? BOOLEAN) ((SELF (ALL-PURPOSE-ITERATOR OF TAXONOMY-NODE))))", ((cpp_function_code)(&allTaxonomyNodesNextP)), NULL);
      defineFunctionObject("FIND-TAXONOMY-NODE", "(DEFUN (FIND-TAXONOMY-NODE TAXONOMY-NODE) ((GRAPH TAXONOMY-GRAPH) (LABEL INTEGER)) :DOCUMENTATION \"Return some node in `graph' with label `label'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&findTaxonomyNode)), NULL);
      defineFunctionObject("LABELED-TAXONOMY-NODE?", "(DEFUN (LABELED-TAXONOMY-NODE? BOOLEAN) ((NODE TAXONOMY-NODE)) :GLOBALLY-INLINE? TRUE (RETURN (DEFINED? (LABEL NODE))))", ((cpp_function_code)(&labeledTaxonomyNodeP)), NULL);
      defineMethodObject("(DEFMETHOD (DELETED? BOOLEAN) ((SELF TAXONOMY-NODE)) :GLOBALLY-INLINE? TRUE (RETURN (EQL? (LABEL SELF) DELETED-LABEL)))", wrapMethodCode(((cpp_method_code)(&TaxonomyNode::deletedP))), NULL);
      defineMethodObject("(DEFMETHOD (DELETED?-SETTER BOOLEAN) ((SELF TAXONOMY-NODE) (VALUE BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&TaxonomyNode::deletedPSetter))), NULL);
      defineFunctionObject("CLEAR-TAXONOMY-NODE", "(DEFUN CLEAR-TAXONOMY-NODE ((NODE TAXONOMY-NODE)) :DOCUMENTATION \"Clear all taxonomy-graph-specific information of `node',\nbut retain information about the native object and associated links.\" :PUBLIC? TRUE)", ((cpp_function_code)(&clearTaxonomyNode)), NULL);
      defineFunctionObject("INITIALIZE-TAXONOMY-NODE", "(DEFUN INITIALIZE-TAXONOMY-NODE ((NODE TAXONOMY-NODE)) :DOCUMENTATION \"Completely clear and initialize `node'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&initializeTaxonomyNode)), NULL);
      defineFunctionObject("HELP-CLEAR-TAXONOMY-GRAPH", "(DEFUN HELP-CLEAR-TAXONOMY-GRAPH ((NODE TAXONOMY-NODE)))", ((cpp_function_code)(&helpClearTaxonomyGraph)), NULL);
      defineFunctionObject("CLEAR-TAXONOMY-GRAPH", "(DEFUN CLEAR-TAXONOMY-GRAPH ((GRAPH TAXONOMY-GRAPH)) :DOCUMENTATION \"Clear all taxonomy-graph-specific information of `graph',\nbut retain information about the native network and associated links.\" :PUBLIC? TRUE)", ((cpp_function_code)(&clearTaxonomyGraph)), NULL);
      defineFunctionObject("INITIALIZE-TAXONOMY-GRAPH", "(DEFUN INITIALIZE-TAXONOMY-GRAPH ((GRAPH TAXONOMY-GRAPH)) :DOCUMENTATION \"Completely clear the taxonomy graph `graph'.\nNOTE: Any nodes associated with `graph' will not be cleared.  If they are\nto be reused, they have to be cleared with `initialize-taxonomy-node'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&initializeTaxonomyGraph)), NULL);
      defineFunctionObject("HELP-CREATE-TAXONOMY-TREE-INTERVALS", "(DEFUN (HELP-CREATE-TAXONOMY-TREE-INTERVALS INTEGER) ((SELF TAXONOMY-NODE)))", ((cpp_function_code)(&helpCreateTaxonomyTreeIntervals)), NULL);
      defineFunctionObject("CREATE-TAXONOMY-TREE-INTERVALS", "(DEFUN CREATE-TAXONOMY-TREE-INTERVALS ((GRAPH TAXONOMY-GRAPH)))", ((cpp_function_code)(&createTaxonomyTreeIntervals)), NULL);
      defineMethodObject("(DEFMETHOD (MEMBER? BOOLEAN) ((INTERVAL INTERVAL) (N INTEGER)) :GLOBALLY-INLINE? TRUE (RETURN (AND (>= N (LOWER-BOUND INTERVAL)) (<= N (UPPER-BOUND INTERVAL)))))", wrapMethodCode(((cpp_method_code)(&Interval::memberP))), NULL);
      defineFunctionObject("SUBINTERVAL-OF?", "(DEFUN (SUBINTERVAL-OF? BOOLEAN) ((SUBINTERVAL INTERVAL) (SUPERINTERVAL INTERVAL)) :GLOBALLY-INLINE? TRUE (RETURN (AND (<= (UPPER-BOUND SUBINTERVAL) (UPPER-BOUND SUPERINTERVAL)) (>= (LOWER-BOUND SUBINTERVAL) (LOWER-BOUND SUPERINTERVAL)))))", ((cpp_function_code)(&subintervalOfP)), NULL);
      defineFunctionObject("MERGE-INTERVALS", "(DEFUN (MERGE-INTERVALS INTERVAL) ((LEFTINTERVAL INTERVAL) (RIGHTINTERVAL INTERVAL)) :GLOBALLY-INLINE? TRUE (RETURN (NEW INTERVAL :LOWER-BOUND (LOWER-BOUND LEFTINTERVAL) :UPPER-BOUND (UPPER-BOUND RIGHTINTERVAL))))", ((cpp_function_code)(&mergeIntervals)), NULL);
      defineFunctionObject("ALL-TAXONOMY-NODE-INTERVALS", "(DEFUN (ALL-TAXONOMY-NODE-INTERVALS (CONS OF INTERVAL)) ((NODE TAXONOMY-NODE)) :GLOBALLY-INLINE? TRUE (RETURN (INTERVALS NODE)))", ((cpp_function_code)(&allTaxonomyNodeIntervals)), NULL);
      defineFunctionObject("INTERN-TAXONOMY-NODE-INTERVAL", "(DEFUN (INTERN-TAXONOMY-NODE-INTERVAL INTERVAL) ((NODE TAXONOMY-NODE) (LOWERBOUND INTEGER) (UPPERBOUND INTEGER)))", ((cpp_function_code)(&internTaxonomyNodeInterval)), NULL);
      defineFunctionObject("ADD-TAXONOMY-NODE-INTERVAL", "(DEFUN ADD-TAXONOMY-NODE-INTERVAL ((NODE TAXONOMY-NODE) (INTERVAL INTERVAL)))", ((cpp_function_code)(&addTaxonomyNodeInterval)), NULL);
      defineFunctionObject("REMOVE-TAXONOMY-NODE-INTERVAL", "(DEFUN REMOVE-TAXONOMY-NODE-INTERVAL ((NODE TAXONOMY-NODE) (INTERVAL INTERVAL)))", ((cpp_function_code)(&removeTaxonomyNodeInterval)), NULL);
      defineFunctionObject("ADJOIN-TAXONOMY-NODE-INTERVAL?", "(DEFUN (ADJOIN-TAXONOMY-NODE-INTERVAL? BOOLEAN) ((NODE TAXONOMY-NODE) (INTERVAL INTERVAL)))", ((cpp_function_code)(&adjoinTaxonomyNodeIntervalP)), NULL);
      defineFunctionObject("PROPAGATE-FOREIGN-INTERVAL", "(DEFUN PROPAGATE-FOREIGN-INTERVAL ((NODE TAXONOMY-NODE) (INTERVAL INTERVAL)))", ((cpp_function_code)(&propagateForeignInterval)), NULL);
      defineFunctionObject("UNCOMPUTE-TOTAL-ANCESTORS", "(DEFUN UNCOMPUTE-TOTAL-ANCESTORS ((NODE TAXONOMY-NODE)))", ((cpp_function_code)(&uncomputeTotalAncestors)), NULL);
      defineFunctionObject("HELP-COMPUTE-TOTAL-ANCESTORS", "(DEFUN HELP-COMPUTE-TOTAL-ANCESTORS ((NODE TAXONOMY-NODE)))", ((cpp_function_code)(&helpComputeTotalAncestors)), NULL);
      defineFunctionObject("COMPUTE-TOTAL-ANCESTORS", "(DEFUN COMPUTE-TOTAL-ANCESTORS ((NODE TAXONOMY-NODE)))", ((cpp_function_code)(&computeTotalAncestors)), NULL);
      defineFunctionObject("CREATE-TAXONOMY-SPANNING-TREE", "(DEFUN CREATE-TAXONOMY-SPANNING-TREE ((GRAPH TAXONOMY-GRAPH) (NODE TAXONOMY-NODE)))", ((cpp_function_code)(&createTaxonomySpanningTree)), NULL);
      defineFunctionObject("CREATE-TAXONOMY-SPANNING-FOREST", "(DEFUN CREATE-TAXONOMY-SPANNING-FOREST ((GRAPH TAXONOMY-GRAPH)))", ((cpp_function_code)(&createTaxonomySpanningForest)), NULL);
      defineFunctionObject("FINALIZE-TAXONOMY-GRAPH", "(DEFUN FINALIZE-TAXONOMY-GRAPH ((GRAPH TAXONOMY-GRAPH)) :DOCUMENTATION \"Finalize the taxonomy graph `graph'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&finalizeTaxonomyGraph)), NULL);
      defineFunctionObject("FINALIZE-TAXONOMY-GRAPH-NONINCREMENTALLY", "(DEFUN FINALIZE-TAXONOMY-GRAPH-NONINCREMENTALLY ((GRAPH TAXONOMY-GRAPH)))", ((cpp_function_code)(&finalizeTaxonomyGraphNonincrementally)), NULL);
      defineFunctionObject("TAXONOMY-SUBNODE-OF?", "(DEFUN (TAXONOMY-SUBNODE-OF? BOOLEAN) ((SUB-NODE TAXONOMY-NODE) (SUPER-NODE TAXONOMY-NODE)) :DOCUMENTATION \"Return TRUE if `sub-node' is a descendant of `super-node'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&taxonomySubnodeOfP)), NULL);
      defineFunctionObject("SLOW-TAXONOMY-SUBNODE-OF?", "(DEFUN (SLOW-TAXONOMY-SUBNODE-OF? BOOLEAN) ((SUBNODE TAXONOMY-NODE) (SUPERNODE TAXONOMY-NODE)))", ((cpp_function_code)(&slowTaxonomySubnodeOfP)), NULL);
      defineFunctionObject("PRINT-TAXONOMY-TREE", "(DEFUN PRINT-TAXONOMY-TREE ((NODE TAXONOMY-NODE) (INDENT INTEGER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printTaxonomyTree)), NULL);
      defineFunctionObject("PRINT-TAXONOMY-GRAPH", "(DEFUN PRINT-TAXONOMY-GRAPH ((GRAPH TAXONOMY-GRAPH) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printTaxonomyGraph)), NULL);
      defineFunctionObject("PRINT-TAXONOMY-SPANNING-TREE", "(DEFUN PRINT-TAXONOMY-SPANNING-TREE ((NODE TAXONOMY-NODE) (INDENT INTEGER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printTaxonomySpanningTree)), NULL);
      defineFunctionObject("PRINT-TAXONOMY-SPANNING-FOREST", "(DEFUN PRINT-TAXONOMY-SPANNING-FOREST ((GRAPH TAXONOMY-GRAPH) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printTaxonomySpanningForest)), NULL);
      defineFunctionObject("STARTUP-TAXONOMIES", "(DEFUN STARTUP-TAXONOMIES () :PUBLIC? TRUE)", ((cpp_function_code)(&startupTaxonomies)), NULL);
      { MethodSlot* function = lookupFunction(SYM_TAXONOMIES_STELLA_STARTUP_TAXONOMIES);

        setDynamicSlotValue(function->dynamicSlots, SYM_TAXONOMIES_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupTaxonomies"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *NUMBERING-INTERVAL* INTEGER 100 :PUBLIC? TRUE :DOCUMENTATION \"Spacing between postorder numbers for nodes.  Allows limited\nincremental insertions without having to renumber the whole graph.\")", &oNUMBERING_INTERVALo);
      defineGlobalVariableObject("(DEFCONSTANT MARKER-LABEL INTEGER -99 :DOCUMENTATION \"Dummy label used for marking a node\")", &MARKER_LABEL);
      defineGlobalVariableObject("(DEFCONSTANT DELETED-LABEL INTEGER -99 :DOCUMENTATION \"Label used for marking deleted nodes\")", &DELETED_LABEL);
      defineGlobalVariableObject("(DEFSPECIAL *TAXONOMY-POSTORDER-NUMBER* INTEGER NULL)", &oTAXONOMY_POSTORDER_NUMBERo);
    }
  }
}

Symbol* SYM_TAXONOMIES_STELLA_STARTUP_TAXONOMIES = NULL;

Symbol* SYM_TAXONOMIES_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
