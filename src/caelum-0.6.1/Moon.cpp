// This file is part of the Caelum project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution.

#include "CaelumPrecompiled.h"
#include "CaelumExceptions.h"
#include "InternalUtilities.h"
#include "Moon.h"
#include <memory>

namespace Caelum
{
    const Ogre::String Moon::MOON_MATERIAL_NAME = "Caelum/PhaseMoon";

    Moon::Moon (
		    Ogre::SceneManager *sceneMgr,
		    Ogre::SceneNode *caelumRootNode, 
		    const Ogre::String& moonTextureName,
		    Ogre::Degree angularSize
    ):
		    BaseSkyLight(sceneMgr, caelumRootNode),
		    mAngularSize(angularSize)
    {
        Ogre::String uniqueSuffix = "/" + InternalUtilities::pointerToString(this);

        // Clone materials
        mMoonMaterial.reset(InternalUtilities::checkLoadMaterialClone(MOON_MATERIAL_NAME, MOON_MATERIAL_NAME + uniqueSuffix));

        assert (!mMoonMaterial.isNull ());
        assert (mMoonMaterial->getTechnique (0));
        assert (mMoonMaterial->getTechnique (0)->getPass (0));
        assert (mMoonMaterial->getTechnique (0)->getPass( 0)->hasFragmentProgram ());
        mParams.setup(mMoonMaterial->getBestTechnique ()->getPass (0)->getFragmentProgramParameters ());

        setMoonTexture(moonTextureName);

	    mMoonBB.reset(sceneMgr->createBillboardSet("Caelum/Moon/MoonBB" + uniqueSuffix, 1));
	    mMoonBB->setMaterialName (mMoonMaterial->getName());
	    mMoonBB->setCastShadows (false);
	    mMoonBB->setRenderQueueGroup (CAELUM_RENDER_QUEUE_MOON);
	    mMoonBB->setDefaultDimensions (1.0f, 1.0f);
	    mMoonBB->createBillboard (Ogre::Vector3::ZERO);

	    mNode->attachObject (mMoonBB.get());
    }

    Moon::~Moon () {
    }

    void Moon::setBodyColour (const Ogre::ColourValue &colour) {
	    BaseSkyLight::setBodyColour(colour);

	    // Set moon material colour.
	    mMoonBB->getBillboard(0)->setColour(colour);
    }

    void Moon::setMoonTexture (const Ogre::String &textureName)
    {
	    // Update the moon material
	    assert(mMoonMaterial->getBestTechnique ());
	    assert(mMoonMaterial->getBestTechnique ()->getPass (0));
	    assert(mMoonMaterial->getBestTechnique ()->getPass (0)->getTextureUnitState (0));
	    mMoonMaterial->getBestTechnique ()->getPass (0)->getTextureUnitState (0)->setTextureName (textureName);
    }

    void Moon::setMoonTextureAngularSize(const Ogre::Degree& moonTextureAngularSize){
	    mAngularSize = moonTextureAngularSize;
    }

    void Moon::notifyCameraChanged (Ogre::Camera *cam) {
        // This calls setFarRadius
        BaseSkyLight::notifyCameraChanged(cam);

        // Set moon position.
        Ogre::Real moonDistance = mRadius - mRadius * Ogre::Math::Tan(mAngularSize);
	    mNode->setPosition(-mDirection * moonDistance);

        // Set moon scaling in [1.0 ~ 1.2] range
        float factor = 1.2f - mBodyColour.b * 0.2f;
        float scale = factor * moonDistance * Ogre::Math::Tan(mAngularSize);
        mNode->setScale (Ogre::Vector3::UNIT_SCALE * scale);
    }

    void Moon::Params::setup(Ogre::GpuProgramParametersSharedPtr fpParams)
    {
        this->fpParams = fpParams;
        this->phase.bind(fpParams, "phase");
    }

    void Moon::setPhase (Ogre::Real phase) {
        mParams.phase.set(mParams.fpParams, phase);	
    }

    void Moon::setMoonNorthPoleDirection(const Ogre::Vector3& moonNorthPoleDir)
    {
        mMoonBB->setBillboardType(Ogre::BBT_ORIENTED_COMMON);
        mMoonBB->setCommonDirection(moonNorthPoleDir);
    }

    void Moon::setQueryFlags (uint flags) {
        mMoonBB->setQueryFlags (flags);
    }

    uint Moon::getQueryFlags () const {
        return mMoonBB->getQueryFlags ();
    }

    void Moon::setVisibilityFlags (uint flags) {
        mMoonBB->setVisibilityFlags (flags);
    }

    uint Moon::getVisibilityFlags () const {
        return mMoonBB->getVisibilityFlags ();
    }
}
