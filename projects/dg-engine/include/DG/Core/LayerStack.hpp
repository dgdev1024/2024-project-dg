/** @file DG/Core/LayerStack.hpp */

#pragma once

#include <DG/Core/Layer.hpp>

namespace dg
{

  class LayerStack
  {
  public:
    LayerStack ();
    ~LayerStack ();

    /**
     * @brief Attaches the given @a `Layer` to this @a `LayerStack`.
     * 
     * @param layer   A handle to the @a `Layer` to attach.
     */
    void attachLayer (Layer& layer);

    /**
     * @brief Detaches the given @a `Layer` from this @a `LayerStack`, if it is attached.
     * 
     * @param layer   A handle to the @a `Layer` to detach.
     */
    void detachLayer (Layer& layer);

  public:
    inline Collection<Layer*>::iterator begin () { return m_layerPtrs.begin(); }
    inline Collection<Layer*>::iterator end () { return m_layerPtrs.end(); }
    inline Collection<Layer*>::const_iterator cbegin () const { return m_layerPtrs.cbegin(); }
    inline Collection<Layer*>::const_iterator cend () const { return m_layerPtrs.cend(); }

    inline Collection<Layer*>::reverse_iterator rbegin () { return m_layerPtrs.rbegin(); }
    inline Collection<Layer*>::reverse_iterator rend () { return m_layerPtrs.rend(); }
    inline Collection<Layer*>::const_reverse_iterator crbegin () const { return m_layerPtrs.crbegin(); }
    inline Collection<Layer*>::const_reverse_iterator crend () const { return m_layerPtrs.crend(); }
    

  private:
    /**
     * @brief The collection of layer pointers stored in this @a `LayerStack`.
     */
    Collection<Layer*> m_layerPtrs;

    /**
     * @brief The index at which the next non-overlay layer should be inserted into this 
     *        @a `LayerStack`.
     */
    Index m_layerInsertIndex = 0;
    
  };

}
