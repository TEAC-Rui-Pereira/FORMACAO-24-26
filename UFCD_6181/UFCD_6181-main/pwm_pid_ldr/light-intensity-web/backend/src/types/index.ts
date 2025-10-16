export interface LightIntensity {
  id: string;
  value: number;
  timestamp: Date;
}

export interface LightControlSettings {
  brightness: number;
  mode: 'auto' | 'manual';
}