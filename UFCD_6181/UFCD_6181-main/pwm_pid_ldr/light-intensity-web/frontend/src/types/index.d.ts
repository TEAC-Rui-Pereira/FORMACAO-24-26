// This file defines TypeScript types and interfaces used throughout the frontend application.

export interface LightIntensity {
  value: number;
  timestamp: string;
}

export interface ApiResponse<T> {
  data: T;
  message: string;
  success: boolean;
}

export interface LightControlSettings {
  intensity: number;
  mode: 'auto' | 'manual';
}