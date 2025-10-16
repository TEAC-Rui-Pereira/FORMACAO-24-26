import { Router } from 'express';
import { getLightIntensity, setLightIntensity } from '../controllers/lightController';

const router = Router();

router.get('/light-intensity', getLightIntensity);
router.post('/light-intensity', setLightIntensity);

export default router;